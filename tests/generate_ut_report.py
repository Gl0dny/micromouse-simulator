#!/usr/bin/env python3

import os
import re
import subprocess
import xml.etree.ElementTree as ET
from lxml import etree
import pdfkit
import json
import logging
from rich.logging import RichHandler
import argparse

logging.basicConfig(level=logging.INFO, format="%(message)s", handlers=[RichHandler()])

XML_REPORT_NAME = 'ut_report.xml'
HTML_REPORT_NAME = 'ut_report.html'
PDF_REPORT_NAME = 'ut_report.pdf'
LCOV_REPORT_NAME = 'coverage.info'

EXCLUDE_DIRS = []

def get_directories():
    """
    Get a list of directories in the current directory, excluding those in EXCLUDE_DIRS.

    Returns:
        list: List of directory names.
    """
    return [dir for dir in os.listdir('.') if os.path.isdir(dir) and dir not in EXCLUDE_DIRS]

def find_first_executable(dir):
    """
    Find the first executable file in the given directory.

    Args:
        dir (str): Directory to search in.

    Returns:
        str: Name of the first executable file found, or None if no executable is found.
    """
    for file in os.listdir(dir):
        file_path = os.path.join(dir, file)
        if os.path.isfile(file_path) and os.access(file_path, os.X_OK):
            # Ignore shared libraries
            if not (file.endswith('.so') or file.endswith('.dll')):
                return file
    return None

def generate_test_report(dir, output_dir):
    """
    Generate a test report for the given directory and output directory.

    Args:
        dir (str): Directory to generate the test report for.
        output_dir (str): Directory to save the generated reports.

    Returns:
        tuple: Paths to the generated test report and coverage file.
    """
    original_dir = os.path.abspath(os.getcwd())
    target_dir = os.path.join(original_dir, "build", dir)
    logging.info(f"Generating test report for {target_dir}")
    
    test_report_file = None
    coverage_file = None

    os.chdir(target_dir)
    executable = find_first_executable(".")
    
    if executable:
        logging.info(f"Running test executable: {executable}")
        executable = f'./{executable}'
        os.environ["GTEST_OUTPUT"] = f"xml:{XML_REPORT_NAME}"
        
        subprocess.run([executable])
        subprocess.run(["lcov", "--capture", "--directory", ".", "--output-file", LCOV_REPORT_NAME])
        
        if os.path.isfile(XML_REPORT_NAME):
            logging.info(f"{target_dir}/{XML_REPORT_NAME}")
            test_report_file = os.path.join(output_dir, XML_REPORT_NAME)
            os.rename(XML_REPORT_NAME, test_report_file)
        else:
            logging.error("Failed to generate test report")
        
        if os.path.isfile(LCOV_REPORT_NAME):
            logging.info(f"{target_dir}/coverage.info")
            coverage_file = os.path.join(output_dir, LCOV_REPORT_NAME)
            os.rename(LCOV_REPORT_NAME, coverage_file)
    else:
        logging.error(f"No test executable found in {target_dir}")

    os.chdir(original_dir)
    return test_report_file, coverage_file

def merge_test_report_with_coverage(project_name, test_report_file, combined_coverage):
    """
    Merge test report XML with coverage data.

    Args:
        project_name (str): Name of the project.
        test_report_file (str): Path to the test report XML file.
        combined_coverage (dict): Combined coverage data.
    """
    tree = ET.parse(test_report_file)
    root = tree.getroot()
    root.set('name', project_name)
    root.set('line_coverage', str(combined_coverage['lines']))
    root.set('function_coverage', str(combined_coverage['functions']))
    
    for testsuite in root.findall('testsuite'):
        testsuite_name = testsuite.get('name')
        if testsuite_name in combined_coverage:
            coverage_data = combined_coverage[testsuite_name]
            testsuite.set('function_coverage', str(coverage_data['functions']))
            testsuite.set('line_coverage', str(coverage_data['lines']))
    
    with open(test_report_file, 'wb') as file:
        tree.write(file)

def parse_lcov_file(filename, cppfile):
    """
    Parse an LCOV file for coverage data specific to a given C++ file.

    Args:
        filename (str): Path to the LCOV file.
        cppfile (str): Name of the C++ file to parse coverage for.

    Returns:
        dict: Coverage data containing lines and functions coverage.
    """
    with open(filename, 'r') as f:
        section_started = False
        section_ended = False
        total_executable_lines = 0
        total_executed_lines = 0
        total_functions = 0
        total_executed_functions = 0

        for line in f:
            parts = line.strip().split(':', 1)
            if not section_started and parts[0] == 'SF' and parts[1].endswith(cppfile):
                section_started = True
            elif parts[0] == 'end_of_record' and section_started:
                section_ended = True
            elif section_started and not section_ended:
                if parts[0] == 'DA':
                    line_no, exec_count = parts[1].split(',')
                    exec_count = int(exec_count)
                    total_executable_lines += 1
                    if exec_count > 0:
                        total_executed_lines += 1
                elif parts[0] == 'FNDA':
                    exec_count, function_name = parts[1].split(',')
                    exec_count = int(exec_count)
                    total_functions += 1
                    if exec_count > 0:
                        total_executed_functions += 1
            elif section_started and section_ended:
                break
        
        coverage_data = {
            'lines': total_executed_lines / total_executable_lines if total_executable_lines > 0 else 0,
            'functions': total_executed_functions / total_functions if total_functions > 0 else 0
        }
    
    return coverage_data

def combine_xml_files(xml_files, output_file):
    """
    Combine multiple XML test report files into a single XML file.

    Args:
        xml_files (list): List of paths to XML files to be combined.
        output_file (str): Path to the output combined XML file.
    """
    total_tests = 0
    total_failures = 0
    total_disabled = 0
    total_errors = 0
    total_time = 0
    total_files_with_coverage = 0
    total_line_coverage = 0
    total_function_coverage = 0
    timestamp = None

    combined_root = ET.Element('testreport')
    
    for xml_file in xml_files:
        tree = ET.parse(xml_file)
        root = tree.getroot()

        total_tests += int(root.attrib['tests'])
        total_failures += int(root.attrib['failures'])
        total_disabled += int(root.attrib['disabled'])
        total_errors += int(root.attrib['errors'])
        total_time += float(root.attrib['time'])
        
        if 'function_coverage' in root.attrib and 'line_coverage' in root.attrib:
            total_files_with_coverage += 1
            total_line_coverage += float(root.attrib['line_coverage'])
            total_function_coverage += float(root.attrib['function_coverage'])

        if timestamp is None:
            timestamp = root.attrib['timestamp']

        combined_root.append(root)

    combined_root.attrib.update({
        'tests': str(total_tests),
        'failures': str(total_failures),
        'disabled': str(total_disabled),
        'errors': str(total_errors),
        'time': str(total_time),
        'timestamp': timestamp,
        'name': 'AllTests'
    })
    
    if total_files_with_coverage > 0:
        combined_root.attrib.update({
            'line_coverage': str(total_line_coverage / total_files_with_coverage),
            'function_coverage': str(total_function_coverage / total_files_with_coverage)
        })

    combined_tree = ET.ElementTree(combined_root)
    combined_tree.write(output_file)

def find_cpp_file(directory):
    """
    Find a C++ source file in the given directory.

    Args:
        directory (str): Directory to search in.

    Returns:
        str: Name of the C++ file found, or None if no file is found.
    """
    for filename in os.listdir(directory):
        logging.info(f"Checking file: {filename}")
        if filename.endswith(".cpp") and not re.match(r'test_[a-zA-Z]\.\d+\.cpp', filename):
            return filename
    return None

def generate_xml_reports(test_plan, project_root, output_dir):
    """
    Generate XML test reports based on the given test plan.

    Args:
        test_plan (dict): Test plan containing unit test directories and test suites.
        project_root (str): Root directory of the project.
        output_dir (str): Directory to save the generated reports.

    Returns:
        str: Path to the generated XML test report.
    """
    report_results = []
    directory = test_plan['unitTestDir']
    directory = os.path.relpath(directory, project_root)

    test_report_file, coverage_file = generate_test_report(directory, output_dir)
    combined_coverage = {}
    total_files_with_coverage = 0
    total_line_coverage = 0
    total_function_coverage = 0

    for test_case in test_plan['testSuites']:
        cppfile = test_case['source']
        if coverage_file and cppfile:
            logging.info(f"Processing test case: {test_case['name']} , cpp file: {cppfile}")
            coverage_data = parse_lcov_file(coverage_file, cppfile)
            if coverage_data['lines'] > 0 and coverage_data['functions'] > 0:
                total_files_with_coverage += 1
                total_line_coverage += coverage_data['lines']
                total_function_coverage += coverage_data['functions']
            coverage_data['file'] = cppfile
            logging.info(f"Coverage data: {coverage_data}")
            combined_coverage[test_case['name']] = coverage_data

    if total_files_with_coverage > 0:
        combined_coverage.update({
            'lines': total_line_coverage / total_files_with_coverage,
            'functions': total_function_coverage / total_files_with_coverage
        })

    logging.info(f"Combined coverage data: {combined_coverage}")
    merge_test_report_with_coverage(test_plan['projectName'], test_report_file, combined_coverage)
    
    return test_report_file

def generate_pdf_report(input_file, output_file, styling_file, output_dir):
    """
    Generate a PDF report from the given XML input file using the specified XSLT styling file.

    Args:
        input_file (str): Path to the input XML file.
        output_file (str): Path to the output PDF file.
        styling_file (str): Path to the XSLT styling file.
        output_dir (str): Directory to save the generated PDF report.
    """
    xml = etree.parse(input_file)
    xslt = etree.parse(styling_file)
    # Create XSLT transformer
    transform = etree.XSLT(xslt)
    # Apply transformation
    result = transform(xml)

    # Save the result to an HTML file in the output directory
    html_file_path = os.path.join(output_dir, HTML_REPORT_NAME)
    with open(html_file_path, 'w') as f:
        f.write(str(result))

    # Convert the HTML file to a PDF
    pdfkit.from_file(html_file_path, output_file)

def main(test_plan, project_root, output_dir, styling_file):
    """
    Main function to generate test reports.

    Args:
        test_plan (dict): Test plan containing unit test directories and test suites.
        project_root (str): Root directory of the project.
        output_dir (str): Directory to save the generated reports.
        styling_file (str): Path to the XSLT styling file.
    """
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    report = generate_xml_reports(test_plan, project_root, output_dir)
    
    if report:
        generate_pdf_report(report, os.path.join(output_dir, PDF_REPORT_NAME), styling_file, output_dir)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate Test Report')
    parser.add_argument('testPlan', type=str, help='Path to the test plan JSON file')
    parser.add_argument('stylingFile', type=str, help='Path to the XSLT styling file')
    parser.add_argument('output_dir', type=str, help='Output directory for the reports')

    args = parser.parse_args()
    project_root = os.getcwd()

    with open(args.testPlan) as f:
        file_data = f.read().replace("${PROJECT_ROOT}", project_root)
        logging.info(f"Test plan: {file_data}")
        data = json.loads(file_data)
        main(data, project_root, args.output_dir, args.stylingFile)
