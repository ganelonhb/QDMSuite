#include "fnggeneratepagehtmlparser.h"
#include "helper_functions.hpp"


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

    bool large = false;
    std::vector<html::node *> buttons = node->select("div#nameGen>input");

    if (buttons.empty())
    {
        buttons = node->select("div#nameGenLarge>input");
        large = true;
    }


    for(html::node * node : buttons)
    {
        QString onclick = QString::fromStdString(node->get_attr("onclick"));
        QRegularExpression re("nameGen\\(([^)]*)\\)");
        QRegularExpressionMatch match = re.match(onclick);

        QString value = makeCaps(QString::fromStdString(node->get_attr("value"))).simplified();

        g.insert(match.captured(1), value);
    }

    std::vector<html::node *> choices = node->select("form#radioChoice>input");

    if (!choices.empty())
    {
        Choices c;

        for (html::node * node : choices)
        {
            QString value = QString::fromStdString(node->get_attr("value"));

            c.insert(value);
        }

        item.choices = c;
    }

    item.genders = g;

    item.large = large;
}
