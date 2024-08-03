#include "fnggeneratepagehtmlparser.h"

#include <iostream>

FNGGeneratePageHTMLParser::FNGGeneratePageHTMLParser()
{}

void FNGGeneratePageHTMLParser::parse(const QString &body)
{
    html::node_ptr node = p.parse(body.toStdString());

    std::vector<html::node *> scripts = node->select("script");

    std::cout << scripts[1]->get_attr("src");


    //std::vector<html::node *> genSection = node->select("div#genSection");
}
