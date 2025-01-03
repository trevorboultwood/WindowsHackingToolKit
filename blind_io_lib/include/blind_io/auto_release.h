#pragma once

#include <functional>
#include <ranges>
namespace bio
{

    template<class T, T Invalid = T{}>
    class AutoRelease
    {
        public:
        AutoRelease() : AutoRelease(Invalid)
        {

        }

        explicit AutoRelease(T obj, std::function<void(T)> deleter = nullptr)
        : obj_(obj)
        , deleter_(deleter)
        {
        }


        AutoRelease(const AutoRelease&) = delete;

        AutoRelease& operator=(const AutoRelease&) = delete;

        AutoRelease(AutoRelease &&other ) : AutoRelease()
        {
            swap(other);
        }

        AutoRelease &operator=(AutoRelease && other)
        {

            AutoRelease new_obj{std::move(other)};
            swap(new_obj);
            return *this;

        }

        ~AutoRelease()
        {
            if((obj_ != Invalid) && deleter_)
            {
                deleter_(obj_);
            }
        }

        T get() const{
            return obj_;
            }

        operator T() const {
            return obj_;
        }

        explicit operator bool() const {
            return obj_ != Invalid;
            }

        bool operator == (const AutoRelease &) const = default;
        bool operator != (const AutoRelease &) const = default;

        void swap(AutoRelease &other)
        {
            std::ranges::swap(obj_, other.obj_);
            std::ranges::swap(deleter_, other.deleter_);
        }



        private:
        T obj_;
        std::function<void(T)> deleter_;
    };

    template<class T, T Invalid>
    void swap(AutoRelease<T, Invalid> &ar1, AutoRelease<T, Invalid> &ar2)
    {
        ar1.swap(ar2);
    }


}