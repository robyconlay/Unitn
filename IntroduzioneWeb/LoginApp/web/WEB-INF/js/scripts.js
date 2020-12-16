/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


function displayProduct(id) {
    let productJSON;
    let product;
    var xhttp = new XMLHttpRequest();
    xhttp.responseType = "json";
    xhttp.open("get", "/product?id=" + id, true);
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            productJSON = this.response;
            product = JSON.parse(this.response);
            document.getElementById("main").innerHTML = `
            <div class="card" id="product-${productJSON.id}">
                <span>${productJSON.name}</span>
                <p><i>${productJSON.price}</i></p>
                <p>${productJSON.description}</p>
            </div>`;
            console.log(productJSON);
        }
    }
    xhttp.send();
}