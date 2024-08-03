#include "fnggeneratepagehtmlparser.h"

#include <iostream>
#include <fstream>

FNGGeneratePageHTMLParser::FNGGeneratePageHTMLParser()
{}

void FNGGeneratePageHTMLParser::parse(const QString &body, FNGGeneratorItem &item)
{
    html::node_ptr node = p.parse(body.toStdString());

    std::vector<html::node *> scripts = node->select("script");

    QString url = "https://www.fantasynamegenerators.com/" + QString::fromStdString(scripts[0]->get_attr("src"));

    QString scriptName = QString::fromStdString(scripts[0]->get_attr("src")).split('/')[1].split('?')[0];

    item.scriptUrl = url;
    item.scriptName = scriptName;

    Genders g;
    std::vector<html::node *> buttons = node->select("div#nameGen>input");


    std::ofstream out;

    out.open("/home/donquixote/.local/share/qdms/log.txt");

    for(html::node * node : buttons)
    {
        QString onclick = QString::fromStdString(node->get_attr("onclick"));
        QRegularExpression re("nameGen\\(([^)]*)\\)");
        QRegularExpressionMatch match = re.match(onclick);

        QString value = QString::fromStdString(node->get_attr("value")).remove("(?i)\bget\b").toLower().simplified();
        QRegularExpression capitalize("(\\b\\w");
        QRegularExpressionMatchIterator i = capitalize.globalMatch(value);

        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();
            int pos = match.capturedStart();
            value[pos] = value[pos].toUpper();
        }

        g.insert(match.captured(1), value);


        std::cout << item.pageUrl.toStdString() << " - " << match.captured(1).toStdString() << " : " << node->get_attr("value") << std::endl;
        out <<item.pageUrl.toStdString() << " - " << match.captured(1).toStdString() << " : " << node->get_attr("value") << std::endl;
    }
    out.close();

    item.genders = g;
}
