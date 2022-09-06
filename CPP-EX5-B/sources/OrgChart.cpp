#include <iostream>
#include "OrgChart.hpp"
#include <algorithm>
#include <queue>

using namespace ariel;

// -------------------------Node Implementation---------------------------------

Node::Node(const std::string &name)
{
    this->name = name;
    this->LevelNext = nullptr;
    this->PreNext = nullptr;
    this->ReverseNext = nullptr;
}

Node::Node(const Node *other)
{
    this->name = other->name;
    this->LevelNext = other->LevelNext;
    this->ReverseNext = other->ReverseNext;
    this->PreNext = other->PreNext;
    for (Node *child : other->children)
    {
        Node *temp = new Node(child);
        this->children.push_back(temp);
    }
}

// -----------------------------------------------------------------------------

// -----------------------Iterator Implementation-------------------------------

OrgChart::Iterator::Iterator(Node *ptr, IteratorType type)
{
    this->p_current_node = ptr;
    this->iter_type = type;
}

std::string OrgChart::Iterator::operator*() const
{
    return p_current_node->name;
}

std::string *OrgChart::Iterator::operator->() const
{
    return &(p_current_node->name);
}

Node *OrgChart::Iterator::get_node()
{
    return this->p_current_node;
}

// ++i;
OrgChart::Iterator &OrgChart::Iterator::operator++()
{
    if (this->iter_type == IteratorType::LevelOrder)
    {
        this->p_current_node = this->p_current_node->LevelNext;
    }
    if (this->iter_type == IteratorType::ReverseOrder)
    {
        this->p_current_node = this->p_current_node->ReverseNext;
    }
    if (this->iter_type == IteratorType::PreOrder)
    {
        this->p_current_node = this->p_current_node->PreNext;
    }
    return *this;
}

// i++;
OrgChart::Iterator OrgChart::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++*this;
    return tmp;
}

bool OrgChart::Iterator::operator==(const Iterator &to_compare) const
{
    return p_current_node == to_compare.p_current_node;
}

bool OrgChart::Iterator::operator!=(const Iterator &to_compare) const
{
    return p_current_node != to_compare.p_current_node;
}

// -----------------------------------------------------------------------------

// -----------------------OrgChart Implementation-------------------------------

OrgChart::OrgChart()
{
    this->root = nullptr;
}

OrgChart &OrgChart::operator=(const OrgChart &other)
{
    if (this != &other)
    {
        if (other.root == nullptr)
        {
            this->root = nullptr;
        }
        else
        {
            this->root = new Node(other.root);
            for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
            {
                Node *node = it.get_node();
                this->all_nodes.push_back(node);
            }
        }
    }
    return *this;
}

OrgChart::OrgChart(const OrgChart &other)
{
    this->root = nullptr;
    *this = other;
}

OrgChart::~OrgChart()
{
    for (Node *ptr : this->all_nodes)
    {
        delete ptr;
    } 
}

void OrgChart::check_errors()
{
    if (this->root == nullptr)
    {
        throw std::logic_error("chart is empty!");
    }
}

OrgChart &OrgChart::add_root(const std::string &root_name)
{
    if (root_name.empty())
    {
        throw std::logic_error("youre trying to add empty name to the chart.");
    }
    if (this->root != nullptr)
    {
        this->root->name = root_name;
    }
    else
    {
        this->root = new Node(root_name);
        this->root->name = root_name;
        this->all_nodes.push_back(root);
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string &boss_name, const std::string &sub_name)
{
    check_errors();
    if (sub_name.empty())
    {
        throw std::logic_error("youre trying to add empty name to the chart.");
    }
    Node *boss = find_name(boss_name);
    if (boss == NULL)
    {
        throw std::logic_error(boss_name + "doesnt exists in the chart");
    }
    Node *sub = new Node(sub_name);
    boss->children.push_back(sub);
    this->all_nodes.push_back(sub);
    return *this;
}

Node *OrgChart::find_name(const std::string &to_find)
{
    for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
    {
        if (*it == to_find)
        {
            return it.get_node();
        }
    }
    return NULL;
}

void OrgChart::LevelOrder()
{
    std::queue<Node *> q;
    std::vector<Node *> l_order;
    q.push(this->root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        l_order.push_back(curr);
        for (uint i = 0; i < curr->children.size(); i++)
        {
            q.push(curr->children[i]);
        }
    }

    for (uint i = 0; i < l_order.size() - 1; i++)
    {
        l_order[i]->LevelNext = l_order[i + 1];
    }
    l_order[l_order.size() - 1]->LevelNext = nullptr;
}

Node *OrgChart::ReverseOrder()
{
    std::queue<Node *> q;
    std::vector<Node *> r_order;
    q.push(this->root);
    int children_size = 0;

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        r_order.push_back(curr);
        children_size = int(curr->children.size());
        for (int i = children_size - 1; i >= 0; i--)
        {
            q.push(curr->children[(uint)i]);
        }
    }
    std::reverse(r_order.begin(), r_order.end());
    for (uint i = 0; i < r_order.size() - 1; i++)
    {
        r_order[i]->ReverseNext = r_order[i + 1];
    }
    r_order[r_order.size() - 1]->ReverseNext = nullptr;
    return r_order[0];
}

void OrgChart::dfs(Node *dfs_root, std::vector<Node *> &p_order)
{
    p_order.push_back(dfs_root);
    for (uint i = 0; i < dfs_root->children.size(); i++)
    {
        dfs(dfs_root->children[i], p_order);
    }
}

void OrgChart::PreOrder()
{
    std::vector<Node *> p_order;
    dfs(this->root, p_order);
    for (uint i = 0; i < p_order.size() - 1; i++)
    {
        p_order[i]->PreNext = p_order[i + 1];
    }
    p_order[p_order.size() - 1]->PreNext = nullptr;
}

OrgChart::Iterator OrgChart::begin_level_order()
{
    check_errors();
    LevelOrder();
    return Iterator(this->root, IteratorType::LevelOrder);
}

OrgChart::Iterator OrgChart::end_level_order()
{
    check_errors();
    return Iterator(nullptr, IteratorType::LevelOrder);
}

OrgChart::Iterator OrgChart::begin_reverse_order()
{
    check_errors();
    Node *reverse_root = ReverseOrder();
    return Iterator(reverse_root, IteratorType::ReverseOrder);
}

OrgChart::Iterator OrgChart::reverse_order()
{
    check_errors();
    return Iterator(nullptr, IteratorType::ReverseOrder);
}

OrgChart::Iterator OrgChart::begin_preorder()
{
    check_errors();
    PreOrder();
    return Iterator(this->root, IteratorType::PreOrder);
}

OrgChart::Iterator OrgChart::end_preorder()
{
    check_errors();
    return Iterator(nullptr, IteratorType::PreOrder);
}

OrgChart::Iterator OrgChart::begin()
{
    return begin_level_order();
}

OrgChart::Iterator OrgChart::end()
{
    return end_level_order();
}

namespace ariel
{

    std::ostream &operator<<(std::ostream &s_out, const OrgChart &org_chart)
    {
        for (uint i = 0; i < org_chart.all_nodes.size(); i++)
        {
            s_out << org_chart.all_nodes[i]->name << " ";
        }
        
        return s_out;
    }

}

// -----------------------------------------------------------------------------
