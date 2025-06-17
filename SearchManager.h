#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <mutex>
#include <functional>
#include <vector>
#include "Product.h"
#include <filesystem>


class SearchManager
{
public:
	static std::shared_ptr<SearchManager> GetInstance();

	void Search(const std::shared_ptr<wxDateTime>& begin, const std::shared_ptr<wxDateTime>& end);

	void Search(const wxDateTime& begin, const wxDateTime& end);

	void Clear();

	std::vector<std::shared_ptr<Product>> GetProducts() const;

private:
	SearchManager() = default;

	std::vector<std::shared_ptr<Product>> m_vctProducts;
	
	static std::mutex s_mtx;

	static std::shared_ptr<SearchManager> s_instance;

};

