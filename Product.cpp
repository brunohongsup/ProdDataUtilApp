#define _CRT_SECURE_NO_WARNINGS

#include "Product.h"
#include <wx/filename.h>
#include <wx/file.h>

Product::Product(const wxString& strId, const wxDateTime& timeStamp, const EJudge eJudge)
    : m_Id(strId)
    , m_timeStamp(timeStamp)
    , m_eJudge(eJudge)
{

}

Product::~Product()
{
	// Destructor logic if needed
}

const wxString& Product::GetId() const
{
    return m_Id;
}

wxDateTime Product::GetTimeStamp() const
{
    return m_timeStamp;
}

wxString Product::GetTimeStampString() const
{
    wxString str;
    str.Format(_T("%04d%02d%02d"), m_timeStamp.GetYear(), m_timeStamp.GetMonth(), m_timeStamp.GetDay());

    return str;
}

const std::vector<wxString>& Product::GetFiles() const
{
    return m_vctFilePath;
}

void Product::AddFile(const wxString& strFilePath)
{
    m_vctFilePath.emplace_back(strFilePath);
}

wxString Product::GetJudge() const
{
    if (m_eJudge == EJudge::OK)
        return _T("OK");

    else if (m_eJudge == EJudge::NG)
        return _T("NG");

    else
        return _T("N/A");
}

std::vector<wxString> Product::GetOverlayImageFiles() const
{
    std::vector<wxString> imageFiles;
    
    for (const auto& filePath : m_vctFilePath) {
        wxFileName fileName(filePath);
        wxString extension = fileName.GetExt().Lower();
        wxString baseName = fileName.GetName().Lower();
        
        // Check if it's a JPG file with "overlay" in the filename
        if ((extension == "jpg" || extension == "jpeg") && baseName.Contains("overlay")) {
            // Verify file exists
            if (wxFile::Exists(filePath)) {
                imageFiles.push_back(filePath);
            }
        }
    }
    
    return imageFiles;
}

