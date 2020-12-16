/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package it.unitn.studenti.robertomazzalai;

import java.util.Objects;

/**
 *
 * @author rob
 */
public class Product {

    private Integer Id;
    private String name;
    private String description;
    private String price;
    private String imgUrl;

    public Product(Integer Id, String name, String description, String price, String imgUrl) {
        this.Id = Id;
        this.name = name;
        this.description = description;
        this.price = price;
        this.imgUrl = imgUrl;
    }

    public Integer getId() {
        return Id;
    }

    public void setId(Integer Id) {
        this.Id = Id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getPrice() {
        return price;
    }

    public void setPrice(String price) {
        this.price = price;
    }

    public String getImgUrl() {
        return imgUrl;
    }

    public void setImgUrl(String imgUrl) {
        this.imgUrl = imgUrl;
    }

    public String toJSON() {
        String template = "{";
        template += " \"id\": " + this.Id;
        template += ", \"name\": \"" + this.name;
        template += "\", \"description\": \"" + this.description;
        template += "\", \"price\": \"" + this.price;
        template += "\", \"imgUrl\": \"" + this.imgUrl;
        template += "\" }";
        
        System.out.println(template);
        
        return template;        
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 71 * hash + Objects.hashCode(this.Id);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Product other = (Product) obj;
        if (!Objects.equals(this.Id, other.Id)) {
            return false;
        }
        return true;
    }

}
