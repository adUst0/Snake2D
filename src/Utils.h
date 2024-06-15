#pragma once

// Local includes

// SDL includes

// std includes

class NonCopyable
{
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
	NonCopyable(NonCopyable&&) = default;
	NonCopyable& operator=(NonCopyable&&) = default;
};

class NonCopyableAndNonMovable
{
public:
	NonCopyableAndNonMovable() = default;
	NonCopyableAndNonMovable(const NonCopyableAndNonMovable&) = delete;
	NonCopyableAndNonMovable& operator=(const NonCopyableAndNonMovable&) = delete;
	NonCopyableAndNonMovable(NonCopyableAndNonMovable&&) = delete;
	NonCopyableAndNonMovable& operator=(NonCopyableAndNonMovable&&) = delete;
};