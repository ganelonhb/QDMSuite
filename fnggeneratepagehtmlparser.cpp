#include "fnggeneratepagehtmlparser.h"

#include <iostream>

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

    for(html::node * node : buttons)
    {
        QString onclick = QString::fromStdString(node->get_attr("onclick"));
        QRegularExpression re("nameGen\\(([^)]*)\\)");
        QRegularExpressionMatch match = re.match(onclick);

        QString value = QString::fromStdString(node->get_attr("value")).toLower().remove("get").simplified();

        g.insert(match.captured(1), value);
    }

    item.genders = g;
}
