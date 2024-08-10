#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include <QStringList>
#include <QString>
#include <QtTypes>
#include <QRegularExpression>

#include <string>
#include <iomanip>
#include <sstream>

inline QString int128ToString(qint128 val)
{
    std::ostringstream oss;

    if (val < 0)
    {
        val = -val;
        oss << '-';
    }

    if (val == 0)
    {
        oss << '0';
        return QString::fromStdString(oss.str());
    }

    char c[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    std::string result;
    while(val != 0)
    {
        int ones = val % 10;
        result.push_back(c[ones]);
        val /= 10;
    }

    std::reverse(result.begin(), result.end());
    oss << result;

    return QString::fromStdString(oss.str());
}


inline QString longDoubleToQString(long double value, int precision = 10) {
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(precision) << value;

    QString answer = QString::fromStdString(oss.str());

    if (answer.endsWith("e+00") || answer.endsWith("e-00"))
        answer = answer.mid(0, answer.length() - 4);
    return answer;
}

inline QString doubleToQString(long double val, int precision = 15)
{
    if (val == static_cast<qint128>(val))
        return int128ToString(static_cast<qint128>(val));

    return longDoubleToQString(val, precision);
}

inline QString minifyJS(const QString &js)
{
    QString minified = js;

    //minified = minified.replace(QRegularExpression(R"((?<![;\{\}\[\(])\n(?![\s]*$))"), ";\n");
    QRegularExpression reNl(R"((?<![;\{\}\[\(])\n(?![\s]*$))");
    minified = minified.replace(reNl, ";");

    // Remove newline characters, comments, and unnecessary whitespace
    minified = minified
                   .remove(QRegularExpression(R"([\n\r])"))
                   .remove(QRegularExpression(R"(//.*)"))
                   .remove(QRegularExpression(R"(/\*.*?\*/)"))
                   .trimmed()
                   .simplified()
                   .replace(QRegularExpression(R"(\s+)"), " ");

    // List of operators and syntax elements to remove spaces around
    QStringList operators = {
        R"(;)", R"(=)", R"(\+)", R"(-)", R"(\*)", R"(/)", R"(%)", R"(!)", R"(==)", R"(!=)", R"(===)", R"(!==)",
        R"(<)", R"(>)", R"(<=)", R"(>=)", R"(&&)", R"(\|\|)", R"(\?)", R"(:)", R"(\()", R"(\))", R"(\{)",
        R"(\})", R"(\[)", R"(\])", R"(,)", R"(\.)"
    };

    // Remove spaces around the operators and syntax elements
    foreach (const QString &op, operators) {
        QString opmin = op;
        opmin = opmin.replace(R"(\)", "");
        minified = minified.replace(QRegularExpression(R"(\s*)" + op + R"(\s*)"), opmin);
    }

    return minified.remove(QRegularExpression("[\x00-\x1F\x7F]"));
}

inline QString makeCaps(const QString& string)
{
    QString newString;

    bool lastWhite = true;
    for (int i = 0; i < string.size(); ++i)
    {
        QString ch = QString(string.at(i));

        if (ch == " " || ch == "\t" || ch == "\n")
        {
            lastWhite = true;
            newString = newString + ch;
            continue;
        }

        newString = newString + (lastWhite ? ch.toUpper() : ch);
        lastWhite = false;
    }

    return newString;
}

inline QString addSpacesToNameAndSimplify(const QString& string)
{
    QString result;
    for (int i = 0; i < string.size(); ++i)
    {
        QChar currentChar = string[i];

        if (currentChar.isPunct() && currentChar != '-' && currentChar != '"' && currentChar != '\'')
            result.append(currentChar).append(' ');
        else if (currentChar == '(' || currentChar == '[' || currentChar == '{')
            result.append(' ').append(currentChar);
        else if (currentChar == ')' || currentChar == ']' || currentChar == '}')
            result.append(currentChar).append(' ');
        else if (currentChar.isUpper() && (i == 0 || (!string[i-1].isSpace() && !string[i-1].isUpper() && !string[i-1].isNumber() && string[i-1] != '-' && string[i-1] != '"' && string[i-1] != '\'')))
            result.append(' ').append(currentChar);
        else
            result.append(currentChar);
    }

    return result.simplified();
}

#endif // HELPER_FUNCTIONS_HPP
