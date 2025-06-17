#include "SearchManager.h"

#include <filesystem>
#include <string>
#include <sstream>

#include "ProdDataUtilApp.h"

std::shared_ptr<SearchManager> SearchManager::s_instance = nullptr;

std::mutex SearchManager::s_mtx{};

std::shared_ptr<SearchManager> SearchManager::GetInstance()
{
	if (nullptr == s_instance)
	{
		std::lock_guard<std::mutex> lock(s_mtx);
		if (nullptr == s_instance)
			s_instance = std::shared_ptr<SearchManager>(new SearchManager());
	}

	return s_instance;
}

void SearchManager::Search(const std::shared_ptr<wxDateTime>& begin, const std::shared_ptr<wxDateTime>& end)
{
	Search(*begin, *end);	
}

void SearchManager::Search(const wxDateTime& begin, const wxDateTime& end)
{
	auto split_cstr = [](const std::string& s, const char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::stringstream ss(s);
		while (std::getline(ss, token, delimiter))
			tokens.push_back(token);
		
		return tokens;
	};

	namespace fs = std::filesystem;
	fs::path root = "D:\\DAT\\IMAGE";
	for (auto it = fs::recursive_directory_iterator(root);it != fs::recursive_directory_iterator();++it)
	{
		if (it->is_directory())
		{
			const int nDepth = it.depth();
			std::string filePath = it->path().string();
			if (filePath.find("Accumulation") != std::string::npos)
			{
				it.disable_recursion_pending();
				continue;
			}

			if (nDepth == 2)
			{
				std::string filePath = it->path().string();
				if (filePath.find("Accumulation") != std::string::npos)
					it.disable_recursion_pending();
				
				std::vector<std::string> vctPath = split_cstr(filePath, _T('\\'));
				if (vctPath.size() >= 3)
				{
					const std::string& day = vctPath.at(vctPath.size() - 1);
					const std::string& month = vctPath.at(vctPath.size() - 2);
					const std::string& year = vctPath.at(vctPath.size() - 3);
					const int nDay = std::stoi(day);
					const int nMonth = std::stoi(month);
					const int nYear = std::stoi(year);
					wxDateTime tmStamp(nDay, wxDateTime::Month(nMonth - 1), nYear);
					if (tmStamp < begin ||  tmStamp > end)
					{
						//ToDo Test When Data Does not match
						it.disable_recursion_pending();
					}
				}
			}
			
			else if (nDepth >= 4)
			{
				std::string filePath = it->path().string();
				std::string strId = it->path().filename().string();
				std::vector<std::string> vctPath = split_cstr(filePath, _T('\\'));
				if (vctPath.size() >= 5)
				{
					const std::string& strJudge = vctPath.at(vctPath.size() - 2);
					EJudge eJudge{};
					if (strJudge == "OK")
						eJudge = EJudge::OK;

					else if (strJudge == "NG")
						eJudge = EJudge::NG;
							
					const std::string& strDay = vctPath.at(vctPath.size() - 3);
					const std::string& strMonth = vctPath.at(vctPath.size() - 4);
					const std::string& strYear = vctPath.at(vctPath.size() - 5);
					const int nDay = std::stoi(strDay);
					const int nMonth = std::stoi(strMonth);
					const int nYear = std::stoi(strYear);
					const auto findProduct = std::find_if(std::begin(m_vctProducts), std::end(m_vctProducts), IdEquals(strId));
					if (findProduct == std::end(m_vctProducts))
					{
						wxDateTime timeStamp{};
						timeStamp.Set(nDay, wxDateTime::Month(nMonth - 1), nYear);
						wxString id(strId.c_str());
						m_vctProducts.emplace_back(std::make_shared<Product>(id, timeStamp, eJudge));
					}

					else
					{
						auto& product = *findProduct;
						auto productTimeStamp = product->GetTimeStamp();
						auto searchedTimeStamp = wxDateTime{};
						searchedTimeStamp.Set(nDay, wxDateTime::Month(nMonth - 1), nYear);
						if (productTimeStamp != searchedTimeStamp)
							continue;
						
						if (eJudge == EJudge::NG)
							product->m_eJudge = eJudge;
					}
				}
			}
		}

		else if (it->is_regular_file())
		{
			fs::path path = it->path();
			fs::path parentPath = path.parent_path();
			std::string id = parentPath.filename().string();
			std::string fileName = path.filename().string();
			if (fileName.find("ProductionData") != std::string::npos)
			{
				it.disable_recursion_pending();
				continue;
			}
			
			const auto findProduct = std::find_if(std::begin(m_vctProducts), std::end(m_vctProducts), IdEquals(id));
			if (findProduct != std::end(m_vctProducts))
			{
				auto& product = *findProduct;
				if (path.extension() == ".jpg")
				{
					wxString str(path.string().c_str());
					product->AddFile(str);
				}

				else if (path.extension() == ".csv")
				{
					if (fileName.find("DayTotal") == std::string::npos)
					{
						wxString str(path.string().c_str());
						product->AddFile(str);
					}
				}
			}
		}
	}
}

void SearchManager::Clear()
{
	m_vctProducts.clear();
}

const std::vector<std::shared_ptr<Product>>& SearchManager::GetProducts() const
{
	return m_vctProducts;
}


