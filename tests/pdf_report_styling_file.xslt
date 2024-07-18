<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html"/>
<xsl:template match="/">
    <html>
    <body>
        <h2>Comets Unit Test Tools Report </h2>
        <h3> Repository : <xsl:value-of select="testsuites/@name"/>  </h3>
        <h3>
            <xsl:element name="table" xmlns="http://www.w3.org/1999/xhtml">
                <xsl:attribute name="border">1</xsl:attribute>
                <xsl:element name="tr">
                    <xsl:element name="td">Total Tests:</xsl:element>
                    <xsl:element name="td"><xsl:value-of select="testsuites/@tests"/></xsl:element>
                </xsl:element>
                <xsl:element name="tr">
                    <xsl:element name="td">Failures:</xsl:element>
                    <xsl:element name="td"><xsl:value-of select="testsuites/@failures"/></xsl:element>
                </xsl:element>
                <xsl:element name="tr">
                    <xsl:element name="td">Disabled:</xsl:element>
                    <xsl:element name="td"><xsl:value-of select="testsuites/@disabled"/></xsl:element>
                </xsl:element>
                <xsl:element name="tr">
                    <xsl:element name="td">Errors:</xsl:element>
                    <xsl:element name="td"><xsl:value-of select="testsuites/@errors"/></xsl:element>
                </xsl:element>
                <xsl:element name="tr">
                    <xsl:element name="td">Total Line Coverage:</xsl:element>
                    <xsl:element name="td"><xsl:value-of select="format-number(testsuites/@line_coverage * 100, '#')"/>%</xsl:element>
                </xsl:element>
                <xsl:element name="tr">
                    <xsl:element name="td">Total Function Coverage:</xsl:element>
                    <xsl:element name="td"><xsl:value-of select="format-number(testsuites/@function_coverage * 100, '#')"/>%</xsl:element>
                </xsl:element>
            </xsl:element>
        </h3>
        <h3> Test Suites </h3>
        <xsl:for-each select="testsuites/testsuite">
            <h4> Test Suite: <xsl:value-of select="@name"/> </h4>
            <xsl:element name="table" xmlns="http://www.w3.org/1999/xhtml">
                    <xsl:attribute name="border">1</xsl:attribute>
                    <xsl:element name="tr">
                        <xsl:element name="td">Test Suite:</xsl:element>
                        <xsl:element name="td"><xsl:value-of select="@name"/></xsl:element>
                    </xsl:element>
                    <xsl:element name="tr">
                        <xsl:element name="td">Number of Test Cases:</xsl:element>
                        <xsl:element name="td"><xsl:value-of select="@tests"/></xsl:element>
                    </xsl:element>
                    <xsl:element name="tr">
                        <xsl:element name="td">Number of Failures:</xsl:element>
                        <xsl:element name="td"><xsl:value-of select="@failures"/></xsl:element>
                    </xsl:element>
                    <xsl:element name="tr">
                        <xsl:element name="td">Line Coverage:</xsl:element>
                        <xsl:element name="td"><xsl:value-of select="format-number(@line_coverage * 100, '#')"/>%</xsl:element>
                    </xsl:element>
                    <xsl:element name="tr">
                        <xsl:element name="td">Function Coverage:</xsl:element>
                        <xsl:element name="td"><xsl:value-of select="format-number(@function_coverage * 100, '#')"/>%</xsl:element>
                    </xsl:element>
                </xsl:element>
            
                
                <table border="1">
                    <tr bgcolor="#9acd32">
            <th style="width: 25%;">Test Case</th>
            <th style="width: 25%;">File Name</th>
            <th style="width: 25%;">Status</th>
            <th style="width: 25%;">Failures</th>
                    </tr>
                    <xsl:for-each select="testcase">
                        <tr>
                            <td style="width: 100px; overflow-wrap: anywhere;"><xsl:value-of select="@name"/></td>
                            <td style="width: 300px; overflow-wrap: anywhere;"><xsl:value-of select="@file"/></td>
                            <td style="width: 100px; overflow-wrap: anywhere;">
                                <xsl:attribute name="bgcolor">
                                    <xsl:choose>
                                        <xsl:when test="failure">red</xsl:when>
                                        <xsl:otherwise>green</xsl:otherwise>
                                    </xsl:choose>
                                </xsl:attribute>
                                <xsl:choose>
                                    <xsl:when test="failure">Failed</xsl:when>
                                    <xsl:otherwise>Passed</xsl:otherwise>
                                </xsl:choose>
                            </td>
                            <td style="width: 300px; overflow-wrap: anywhere;">
                                <xsl:for-each select="failure">
                                    <div style="white-space: pre;"><xsl:value-of select="."/></div>
                                </xsl:for-each>
                            </td>
                        </tr>
                    </xsl:for-each>
                </table>
             <xsl:element name="hr" xmlns="http://www.w3.org/1999/xhtml" />
             <xsl:element name="hr" xmlns="http://www.w3.org/1999/xhtml" />
             <xsl:element name="hr" xmlns="http://www.w3.org/1999/xhtml" />
             <xsl:element name="hr" xmlns="http://www.w3.org/1999/xhtml" />
            
        </xsl:for-each>
    </body>
    </html>
</xsl:template>
</xsl:stylesheet>