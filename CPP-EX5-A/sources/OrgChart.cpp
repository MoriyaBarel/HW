#include <iostream>
#include "OrgChart.hpp"

using namespace ariel;

OrgChart::OrgChart()
{
    this->root = NULL;
}

OrgChart &OrgChart::add_root(const std::string &root)
{
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string &boss, const std::string &sub)
{
    return *this;
}

OrgChart::Iterator OrgChart::begin_level_order()
{
    Iterator iter;
    return iter;
}

OrgChart::Iterator OrgChart::end_level_order()
{
    Iterator iter;
    return iter;
}

OrgChart::Iterator OrgChart::begin_reverse_order()
{
    Iterator iter;
    return iter;
}

OrgChart::Iterator OrgChart::reverse_order()
{
    Iterator iter;
    return iter;
}

OrgChart::Iterator OrgChart::begin_preorder()
{
    Iterator iter;
    return iter;
}

OrgChart::Iterator OrgChart::end_preorder()
{
    Iterator iter;
    return iter;
}

OrgChart::Iterator OrgChart::begin()
{
    Iterator iter;
    return iter;
}

OrgChart::Iterator OrgChart::end()
{
    Iterator iter;
    return iter;
}

namespace ariel
{

    std::ostream &operator<<(std::ostream &s_out, const OrgChart &org_chart)
    {
        return s_out;
    }

}
