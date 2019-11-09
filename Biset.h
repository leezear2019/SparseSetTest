//
// Created by 李哲 on 2019/11/9.
//

#ifndef SPARSESETTEST_BISET_H
#define SPARSESETTEST_BISET_H

#include <vector>

namespace CTRL {

    class Biset;

    class Iterator {
    public:
        friend class Biset;

        // 取值
        int Value() const noexcept;

        int Index() const noexcept;

        bool IsFormerBegin() const noexcept;

        bool IsLatterBegin() const noexcept;

        bool IsFormerEnd() const noexcept;

        bool IsLatterEnd() const noexcept;

        bool BeforeFormerBegin() const noexcept;

        bool BeforeLatterBegin() const noexcept;

        bool AfterFormerEnd() const noexcept;

        bool AfterLatterEnd() const noexcept;

        void operator++() noexcept;

        void operator--() noexcept;

        void MoveToLatterAndGoPrevious() noexcept;

        void MoveToLatter() noexcept;

        void MoveToFormer() noexcept;

        void MoveToFormerAndGoNext() noexcept;

    private:
        Iterator(Biset *s, int i);

        void previous() noexcept;

        void next() noexcept;

        int i_;
        int length_;
        Biset *s_;
    };


    // 二部集合，集合中元素不是属于上一类就是属于下一类，其中上一个集合称为former,后一个集合称为latter
    // 采用稀疏集的数据结构
    class Biset {
    public:
        friend class Iterator;

        Biset();

        // 初始化时所有的元素都属于former集合
        explicit Biset(int size);

        void Reserve(int size);

        // 标记一个状态
        void Mark();

        // 回到设定的状态
        void BackToMark();

        bool BelongToFront(int a) const noexcept;

        bool BelongToLatter(int a) const noexcept;

        void MoveElementToLatter(int a) noexcept;

        void MoveElementToFormer(int a) noexcept;

        int FormerSize() const noexcept;

        int LatterSize() const noexcept;

        void MoveAllToFormer() noexcept;

        void MoveAllToLatter() noexcept;

        Iterator FormerBegin() noexcept;

        Iterator LatterBegin() noexcept;

        Iterator FormerEnd() noexcept;

        Iterator LatterEnd() noexcept;

    private:
        inline void swap(const int i, const int j) noexcept;

        int getValue(const int i) const noexcept;

        std::vector<int> dense_;
        std::vector<int> sparse_;

        //  sep_index_用来分隔两个集合，sep_index(不含sep_index_)之前的所有元素属于former,
        //  默认都属于former
        int sep_;

        // 标记一个状态用于回溯
        int mark_;

        // 总长度
        int size_;
    };

}


#endif //SPARSESETTEST_BISET_H
