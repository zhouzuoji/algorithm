#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

template<class ConstInputIterator>
decltype(*declval<ConstInputIterator>()) sum_of_range(ConstInputIterator first, ConstInputIterator last) {
    std::remove_const<std::remove_reference<decltype(*first)>::type>::type ans=0;
    while (first!=last) ans+=*(first++);
    return ans;
}

template<class ConstInputIterator>
decltype(*declval<ConstInputIterator>()) min_in_range(ConstInputIterator first, ConstInputIterator last) {
    ConstInputIterator ans=first;
    while (++first!=last) 
        if (*first<*ans) ans=first;
    return *ans;
}

template<class ConstInputIterator>
decltype(*declval<ConstInputIterator>()) max_in_range(ConstInputIterator first, ConstInputIterator last) {
    ConstInputIterator ans=first;
    while (++first!=last) 
        if (*first>*ans) ans=first;
    return *ans;
}

template<class T> 
struct ListNodeTemplate {
    T val;
    ListNodeTemplate *next;
    ListNodeTemplate(T x) : val(x), next(nullptr) {}
};

typedef ListNodeTemplate<int> ListNode;
typedef const char* PChar;

template<class T> 
class Array2D {
public:
    inline Array2D() {}
    inline Array2D(size_t numRows, size_t numCols): m_numRows(numRows), m_numCols(numCols) {
        m_items.resize(numRows*numCols);
    }
    inline void resize(size_t numRows, size_t numCols) { 
        m_numRows=numRows, m_numCols=numCols, m_items.resize(numRows*numCols); 
    }
    inline T getValue(size_t rowIdx, size_t colIdx) const { return m_items[rowIdx*m_numCols+colIdx]; }
    inline T& get(size_t rowIdx, size_t colIdx) { return m_items[rowIdx*m_numCols+colIdx]; }
    inline const T& get(size_t rowIdx, size_t colIdx) const { return m_items[rowIdx*m_numCols+colIdx]; } 
    inline void set(size_t rowIdx, size_t colIdx, const T& v) { m_items[rowIdx*m_numCols+colIdx]=v; }   
private:
    size_t m_numRows, m_numCols;
    vector<T> m_items; 
};

namespace json {
    template<class T>
    inline void print(std::ostream& os, const T& val) { os << val; }

    template<>
    inline void print(std::ostream& os, const std::string& val) { os << '"' << val << '"'; }

    template<>
    inline void print(std::ostream& os, const PChar& val) { os << '"' << val << '"'; }

    template<>
    inline void print(std::ostream& os, const char& val) { os << "'" << val << "'"; }

    template<class _KeyT, class _ValT>
    inline void operator<<(std::ostream& os, const std::pair<_KeyT, _ValT>& kv) {
        print(os, kv.first);
        os << ": ";
        print(os, kv.second);
    }

    template<class _Iterator, class _Bracket>
    void print(std::ostream& os, _Iterator first, _Iterator last, const _Bracket& left, const _Bracket& right) {
        os << left;
        if (first != last) {
            print(os, *first);
            while (++first != last) {
                os << ", ";
                print(os, *first);
            }
        }
        os << right;
    }


    template<class T>
    inline void operator<<(std::ostream& os, const std::vector<T>& arr) {
        print(os, arr.begin(), arr.end(), '[', ']');
    }

    template<class T>
    inline void operator<<(std::ostream& os, const std::set<T>& arr) {
        print(os, arr.begin(), arr.end(), '[', ']');
    }

    template<class T>
    inline void operator<<(std::ostream& os, const std::unordered_set<T>& arr) {
        print(os, arr.begin(), arr.end(), '[', ']');
    }

    template<class _KeyT, class _ValT>
    inline void operator<<(std::ostream& os, const std::unordered_map<_KeyT, _ValT>& dict) {
        print(os, dict.begin(), dict.end(), '{', '}');
    }

    template<class _KeyT, class _ValT>
    inline void operator<<(std::ostream& os, const std::map<_KeyT, _ValT>& dict) {
        print(os, dict.begin(), dict.end(), '{', '}');
    }

    template<class T>
    static std::string stringify(const T& val) {
        std::ostrstream ss;
        print(os, val);
        return ss.str();
    }
};

template<class T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& arr) {
    json::print(os, arr.begin(), arr.end(), '[', ']');
    return os;
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const std::set<T>& arr) {
    json::print(os, arr.begin(), arr.end(), '[', ']');
    return os;
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& arr) {
    json::print(os, arr.begin(), arr.end(), '[', ']');
    return os;
}

template<class _KeyT, class _ValT>
inline std::ostream& operator<<(std::ostream& os, const std::unordered_map<_KeyT, _ValT>& dict) {
    json::print(os, dict.begin(), dict.end(), '{', '}');
    return os;
}

template<class _KeyT, class _ValT>
inline std::ostream& operator<<(std::ostream& os, const std::map<_KeyT, _ValT>& dict) {
    json::print(os, dict.begin(), dict.end(), '{', '}');
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const ListNodeTemplate<T>* list) {
    if (!list) 
        os << "null";
    else {
        json::print(os, list->val);
        while(list=list->next) {
            os << ", ";
            json::print(os, list->val);
        }
    }
    return os;
}

vector<int> randomInts(size_t n) {
    vector<int> ans(n);
    for(size_t i=0;i<n;++i)
        ans[i]=rand();
    return ans;
}

