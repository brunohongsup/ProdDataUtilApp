#include "ProdDataUtilFrameDerived.h"
#include "Product.h"

class ProductTreeItemData : public wxTreeItemData
{
private:
    std::shared_ptr<Product> m_product;
    
public:
    ProductTreeItemData(std::shared_ptr<Product> product) 
        : m_product(product) {}
    
    std::shared_ptr<Product> GetProduct() const { return m_product; }
    
    Product* GetProductPtr() const { return m_product.get(); }
    
    void ClearProduct() { m_product.reset(); }
    
    bool IsValid() const { return m_product != nullptr; }
};