#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <vector>
#include <string>
#include <wx/string.h>
#include <wx/datetime.h>

enum class EJudge : uint8_t
{
	Default = 0,
	OK = 1,
	NG = 2
};

class Product
{

	friend class SearchManager;
public:
	
	Product(const wxString& strId, const wxDateTime& timeStamp, const EJudge eJudge);

	Product() = delete;

	virtual ~Product();

	const wxString& GetId() const;

	wxDateTime GetTimeStamp() const;

	wxString GetTimeStampString() const;

	const std::vector<wxString>& GetFiles() const;

	void AddFile(const wxString& strFilePath);

	wxString GetJudge() const;

	// Get image files with "overlay" in the filename
	std::vector<wxString> GetOverlayImageFiles() const;

private:
	wxString m_Id;

	wxDateTime m_timeStamp;

	std::vector<wxString> m_vctFilePath;

	EJudge m_eJudge;
};

struct IdEquals
{
	wxString strTargetId;
	IdEquals(const wxString& id)
		: strTargetId(id)
	{
		
	}

	IdEquals(const std::string& str)
		: strTargetId(str.c_str())
	{
		
	}

	bool operator()(const Product& product) const
	{
		return product.GetId() == strTargetId;
	}

	bool operator()(const std::shared_ptr<Product>& product) const
	{
		return product->GetId() == strTargetId;
	}

	bool operator()(const std::unique_ptr<Product>& product) const
	{
		return product->GetId() == strTargetId;
	}
};
