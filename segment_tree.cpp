template<typename T>
struct node {
    T value, modifier;

    node(const T &val, const T &modifier) {
        value = val;
        this->modifier = modifier;
    }

    node() {}

};

template<typename T>
struct segment_tree {
private:
    node<T> *tree;
    unsigned size, capacity;

    T (*operate)(T&, T&);

    void (*change)(T&, T&);

    T neutral, neutral_modifier;

public:

    segment_tree(T *array, const unsigned &size, T (*operation)(T&, T&), void (*change)(T&, T&), const T &neutral,
                 const T &neutral_modifier) {
        operate = operation;
        this->change = change;
        this->neutral = neutral;
        this->neutral_modifier = neutral_modifier;
        this->size = size;
        capacity = 2;
        while (capacity < size) {
            capacity <<= 2;
        }
        tree = new node<T>[capacity * 2 + 10];
        build(0, 0, capacity, array);
    }

    T get(int l, int r) {
        return get(l, r, 0, capacity, 0);
    }

    void set(int l, int r, T modifier) {
        set(l, r, modifier, 0, capacity, 0);
    }

private:

    void build(int idx, int l, int r, T *array) {
        if (r - l == 1) {
            tree[idx] = l < size ? node<T>(array[l], neutral_modifier) : node<T>(neutral, neutral_modifier);
            return;
        }
        int m = (l + r) / 2;

        build(2 * idx + 1, l, m, array);
        build(2 * idx + 2, m, r, array);

        tree[idx] = node<T>(operate(tree[idx * 2 + 1].value, tree[idx * 2 + 2].value), neutral_modifier);

    }

    void propagate(int idx, int lx, int rx) {
        int li = 2 * idx + 1, ri = li + 1;
        change(tree[idx].value, tree[idx].modifier);

        if (rx - lx == 1) {
            tree[idx].modifier = neutral_modifier;
            return;
        }

        change(tree[li].modifier, tree[idx].modifier);

        change(tree[ri].modifier, tree[idx].modifier);

        tree[idx].modifier = neutral_modifier;
    }

    T get(int l, int r, int lx, int rx, int idx) {
        propagate(idx, lx, rx);
        if (l >= rx || r <= lx) {
            return neutral;
        }
        if (l <= lx && rx <= r) {
            return tree[idx].value;
        }

        int m = (rx + lx) / 2;
        T a = get(l, r, lx, m, 2 * idx + 1),
        b = get(l, r, m, rx, 2 * idx + 2);

        return operate(a, b);
    }

    void set(int l, int r, T modifier, int lx, int rx, int idx) {
        propagate(idx, lx, rx);
        if (l >= rx || r <= lx) {
            return;
        }
        if (lx >= l && rx <= r) {
            change(tree[idx].modifier, modifier);
            propagate(idx, lx, rx);
            return;
        }

        int m = (lx + rx) / 2;
        set(l, r, modifier, lx, m, 2 * idx + 1);
        set(l, r, modifier, m, rx, 2 * idx + 2);
        tree[idx].value = operate(tree[2 * idx + 1].value, tree[2 * idx + 2].value);
    }

};
