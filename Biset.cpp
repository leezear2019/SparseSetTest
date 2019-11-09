//
// Created by 李哲 on 2019/11/9.
//

#include "Biset.h"

namespace CTRL {

    Biset::Biset() {

    }

    Biset::Biset(const int size) :
            size_(size) {
        sep_ = size;
        mark_ = size;
        dense_.resize(size);
        sparse_.resize(size);

        for (int i = 0; i < size_; ++i) {
            dense_[i] = i;
            sparse_[i] = i;
        }
    }

    void Biset::Reserve(const int size) {
        size_ = size;
        sep_ = size;
        mark_ = size;
        dense_.reserve(size);
        sparse_.reserve(size);

        for (int i = 0; i < size_; ++i) {
            dense_[i] = i;
            sparse_[i] = i;
        }
    }


    void Biset::Mark() {
        mark_ = sep_;
    }

    void Biset::BackToMark() {
        sep_ = mark_;

    }

    bool Biset::BelongToFront(const int a) const noexcept {
        return sparse_[a] < sep_;
    }

    bool Biset::BelongToLatter(const int a) const noexcept {
        return sparse_[a] >= sep_;
    }

    void Biset::MoveElementToLatter(const int a) noexcept {
        if (BelongToFront(a)) {
            swap(sparse_[a], --sep_);
        }
    }

    void Biset::MoveElementToFormer(const int a) noexcept {
        if (BelongToLatter(a)) {
            swap(sep_++, sparse_[a]);
        }
    }

    void Biset::swap(const int i, const int j) noexcept {
        int tmp = dense_[i];
        dense_[i] = dense_[j];
        dense_[j] = tmp;

        sparse_[dense_[i]] = i;
        sparse_[dense_[j]] = j;
    }

    int Biset::getValue(const int i) const noexcept {
        return dense_[i];
    }

    int Biset::FormerSize() const noexcept {
        return sep_;
    }

    int Biset::LatterSize() const noexcept {
        return size_ - sep_;
    }

    void Biset::MoveAllToFormer() noexcept {
        sep_ = size_;
    }

    void Biset::MoveAllToLatter() noexcept {
        sep_ = 0;
    }

    Iterator Biset::LatterEnd() noexcept {
        return Iterator(this, size_);
    }

    Iterator Biset::FormerBegin() noexcept {
        return Iterator(this, 0);
    }

    Iterator Biset::LatterBegin() noexcept {
        return Iterator(this, sep_);
    }

    Iterator Biset::FormerEnd() noexcept {
        return Iterator(this, sep_ - 1);
    }

    //////////////////////////////////////////////////////////////////////////////////////

    Iterator::Iterator(Biset *s, const int i) :
            s_(s),
            i_(i),
            length_(s->size_) {}

    int Iterator::Value() const noexcept {
        return s_->getValue(i_);
    }

    int Iterator::Index() const noexcept {
        return i_;
    }

    bool Iterator::IsFormerBegin() const noexcept {
        return i_ == 0;
    }

    bool Iterator::IsLatterBegin() const noexcept {
        return i_ == s_->sep_;
    }

    bool Iterator::IsFormerEnd() const noexcept {
        return i_ == s_->sep_ - 1;
    }

    bool Iterator::IsLatterEnd() const noexcept {
        return i_ == length_ - 1;
    }

    bool Iterator::BeforeFormerBegin() const noexcept {
        return i_ < 0;
    }

    bool Iterator::BeforeLatterBegin() const noexcept {
        return i_ < s_->sep_;
    }

    bool Iterator::AfterFormerEnd() const noexcept {
        return i_ >= s_->sep_;
    }

    bool Iterator::AfterLatterEnd() const noexcept {
        return i_ >= length_;
    }

    void Iterator::operator--() noexcept {
        --i_;
    }

    void Iterator::operator++() noexcept {
        ++i_;
    }

    void Iterator::previous() noexcept {
        --i_;
    }

    void Iterator::next() noexcept {
        ++i_;
    }

    void Iterator::MoveToLatterAndGoPrevious() noexcept {
        s_->MoveElementToLatter(s_->dense_[i_]);
        previous();
    }

    void Iterator::MoveToLatter() noexcept {
        s_->MoveElementToLatter(s_->dense_[i_]);
    }

    void Iterator::MoveToFormer() noexcept {
        s_->MoveElementToFormer(s_->dense_[i_]);
    }

    void Iterator::MoveToFormerAndGoNext() noexcept {
        s_->MoveElementToFormer(s_->dense_[i_]);
        next();
    }


}