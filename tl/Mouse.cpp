#include "Mouse.h"
#include "Impl.h"

auto tl::input::mouse::getLatestLocation()->tl::datatypes::Point {
    return tl::impl::mouse::latestLocation;
}