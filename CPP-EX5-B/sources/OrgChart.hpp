#include <iostream>
#include <vector>

namespace ariel
{
    class Node
    {
    public:
        std::string name;
        Node *LevelNext;
        Node *ReverseNext;
        Node *PreNext;
        std::vector<Node *> children;
        Node(const std::string &name);
        Node(const Node *other);
    };

    class OrgChart
    {
    private:
        Node *root;
        std::vector<Node *> all_nodes;
        Node *find_name(const std::string &to_find);
        void LevelOrder();
        Node *ReverseOrder();
        void PreOrder();
        void dfs(Node *dfs_root, std::vector<Node *> &p_order);
        void check_errors();

    public:
        enum class IteratorType
        {
            LevelOrder,
            ReverseOrder,
            PreOrder
        };

        class Iterator
        {
        private:
            Node *p_current_node;
            IteratorType iter_type;

        public:
            Iterator(Node *ptr, IteratorType type);
            std::string operator*() const;
            std::string *operator->() const;
            Node *get_node();
            Iterator &operator++();   // ++i;
            Iterator operator++(int); // i++;
            bool operator==(const Iterator &to_compare) const;
            bool operator!=(const Iterator &to_compare) const;
        };

        OrgChart();
        OrgChart(const OrgChart &other);
        OrgChart(OrgChart &&other) noexcept = default;
        ~OrgChart();
        OrgChart &operator=(const OrgChart &other);
        OrgChart &operator=(OrgChart &&other) noexcept = default;
        OrgChart &add_root(const std::string &root_name);
        OrgChart &add_sub(const std::string &boss_name, const std::string &sub_name);
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