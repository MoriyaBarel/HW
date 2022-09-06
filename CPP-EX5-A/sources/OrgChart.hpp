#include <iostream>
#include <vector>

namespace ariel
{

    class Node
    {
    public:
        std::string data;
        Node *next;
        std::vector<Node *> children;
    };

    class OrgChart
    {
    private:
        Node *root;

    public:
        class Iterator
        {
        private:
            Node *p_current_node;

        public:
            Iterator(Node *ptr = nullptr) : p_current_node(ptr)
            {
            }

            std::string operator*() const
            {
                if (p_current_node == NULL)
                {
                    return " ";
                }
                return p_current_node->data;
            }

            std::string *operator->() const
            {
                return &(p_current_node->data);
            }

            // ++i;
            Iterator &operator++()
            {
                // p_current_node = p_current_node->next;
                return *this;
            }

            // i++;
            Iterator operator++(int)
            {
                Iterator tmp = *this;
                // p_current_node = p_current_node->next;
                return tmp;
            }

            bool operator==(const Iterator &rhs) const
            {
                return p_current_node->data == rhs.p_current_node->data;
            }

            bool operator!=(const Iterator &rhs) const
            {
                // return p_current_node->data != rhs.p_current_node->data;
                return false;
            }
        };

        OrgChart();
        OrgChart &add_root(const std::string &root);
        OrgChart &add_sub(const std::string &boss, const std::string &sub);
        Iterator begin_level_order();
        Iterator end_level_order();
        Iterator begin_reverse_order();
        Iterator reverse_order();
        Iterator begin_preorder();
        Iterator end_preorder();
        Iterator begin();
        Iterator end();

        friend std::ostream &operator<<(std::ostream &s_out, const OrgChart &org_chart); // cout
    };
}