<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"/>
    <xsl:template match="/">
        <html>
            <head>
                <style type="text/css">
                    h2{color:#0860a8;font-size:200%;margin-left: 0pt;margin-bottom: 0px;font-weight:normal;}
                    h3{color:#000000;font-size:120%;margin-left: 0pt;margin-bottom: 0px;font-weight:normal;}
                    table{margin-bottom:5pt;border-collapse:collapse;margin-left:0px;margin-top:0.3em;}
                    th{border:1px solid grey;padding-top:0px;padding-bottom:0px;padding-right:3px;padding-left:3px;text-align:left;color:white;background-color:#555555;font-size:110%;font-weight:bold;}
                    td.file{text-align:left;border:1px solid grey;}
                    td.function{text-align:left;border:1px solid grey;}
                    td.value{text-align:right;border:1px solid grey;}
                    td.noborder{text-align:left;border:0px;}
                </style>
            </head>

            <body>

                <div id="container">

                    <div id="header" style="width:100%;height:10%;fixed">
                        <h2>Cyclomatic Complexity Metrics</h2>
                    </div>

                    <hr/>

                    <div id="table">
                        <xsl:variable name="N">20</xsl:variable>
                        <h3>
                            Top <xsl:value-of select="$N"/> most complex functions
                        </h3>
                        <table class="border" cellpadding="5">
                            <tr bgcolor="#C0C0C0">
                                <th>Complexity</th>
                                <th>Function</th>
                                <th>File(line)</th>
                            </tr>
                            <xsl:for-each select="//func">
                                <xsl:sort order="descending" select="@value" data-type="number"/>
                                <xsl:sort order="ascending" select="ancestor::file/@name" data-type="text"/>
                                <xsl:sort order="ascending" select="@line" data-type="number"/>
                                <xsl:if test="position() &lt;= $N">
                                    <tr>
                                        <td class="value">
                                            <xsl:value-of select="@value"/>
                                        </td>
                                        <td class="function">
                                            <xsl:element name="a">
                                                <xsl:attribute name="title">
                                                    <xsl:value-of select="@name"/>
                                                </xsl:attribute>
                                                <xsl:value-of select="@short_name"/>
                                            </xsl:element>
                                        </td>
                                        <td class="file">
                                            <xsl:element name="a">
                                                <xsl:attribute name="title">
                                                    <xsl:value-of select="ancestor::file/@name"/>
                                                </xsl:attribute>
                                                <xsl:call-template name="basename">
                                                    <xsl:with-param name="name" select="ancestor::file/@name"/>
                                                </xsl:call-template>
                                            </xsl:element>
                                            (<xsl:value-of select="@line"/>)
                                        </td>
                                    </tr>
                                </xsl:if>
                            </xsl:for-each>
                        </table>
                        <br/>
                        <br/>
                    </div>

                    <div id="footer">
                        <h3>Full list of functions</h3>
                        <table class="border" cellpadding="5">
                            <tr bgcolor="#C0C0C0">
                                <th>Function</th>
                                <th>File(line)</th>
                                <th>Complexity</th>
                            </tr>
                            <xsl:for-each select="//func">
                                <xsl:sort order="descending" select="@value" data-type="number"/>
                                <xsl:sort order="ascending" select="ancestor::file/@name" data-type="text"/>
                                <xsl:sort order="ascending" select="@line" data-type="number"/>
                                <tr>
                                    <td class="function">
                                        <xsl:element name="a">
                                            <xsl:attribute name="title">
                                                <xsl:value-of select="@name"/>
                                            </xsl:attribute>
                                            <xsl:value-of select="@short_name"/>
                                        </xsl:element>
                                    </td>
                                    <td class="file">
                                        <xsl:element name="a">
                                            <xsl:attribute name="title">
                                                <xsl:value-of select="ancestor::file/@name"/>
                                            </xsl:attribute>
                                            <xsl:call-template name="basename">
                                                <xsl:with-param name="name" select="ancestor::file/@name"/>
                                            </xsl:call-template>
                                        </xsl:element>
                                        (<xsl:value-of select="@line"/>)
                                    </td>
                                    <td class="value">
                                        <xsl:value-of select="@value"/>
                                    </td>
                                </tr>
                            </xsl:for-each>
                        </table>
                    </div>
                </div>
            </body>
        </html>
    </xsl:template>

    <xsl:template name="basename">
        <xsl:param name="name"/>
        <xsl:choose>
            <xsl:when test="contains($name, '\')">
                <xsl:call-template name="basename">
                    <xsl:with-param name="name" select="substring-after($name,'\')"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test="contains($name, '/')">
                <xsl:call-template name="basename">
                    <xsl:with-param name="name" select="substring-after($name, '/')"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="$name"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

</xsl:stylesheet>

