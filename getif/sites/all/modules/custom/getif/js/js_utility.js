function showLoadAnimation(item){

    Drupal.behaviors.jquery_loadinganimation.Loadinganimation.show();

    item.form.submit();
}

/**
 * Verifica se il browser è Internet Explorer
 * @returns {boolean} : true if IE, false altrimenti
 */
function isIEBrowser() {
    var ua = window.navigator.userAgent;
    var msie = ua.indexOf("MSIE ");

    if (msie > 0 || !!navigator.userAgent.match(/Trident.*rv\:11\./))  // If Internet Explorer, return version number
    {
        return true;
    }

    return false;
}

/**
 * Converte una stringa base64 (COMPLETA) in un array
 * @param data : stringa base64 completa
 * @returns {Uint8Array} : array convertito corrispondente al base64
 */
function base64ToArrayBuffer(data) {
    data = data.replace(/^[^,]+,/, '');
    data = data.replace(/\s/g, '');

    var binaryString = atob(data);
    var binaryLen = binaryString.length;
    var bytes = new Uint8Array(binaryLen);

    for (var i = 0; i < binaryLen; i++) {
        bytes[i] = binaryString.charCodeAt(i);
    }

    return bytes;
}

/**
 * Marco Rodella 02-07-2018
 * Scartata per non funziona con IE
 */
// function scaricaFile(dataurl, filename) {
//
//     var a = document.createElement("a");
//     a.setAttribute("download", filename);
//     a.href = dataurl;
//     // a.setAttribute("target", "_blank");
//     var b = document.createEvent("MouseEvents");
//     b.initEvent("click", false, true);
//     a.dispatchEvent(b);
//
//     return false;
// }

function scaricaFile(dataurl, filename) {

    var contentType = 'application/pdf';

    // Converto in array il mio base64 così da poter creare un blob
    var arrBuffer = base64ToArrayBuffer(dataurl);

    // Creo il blob
    var file = new Blob([arrBuffer], {type: contentType});

    // Creo il link fittizio che scaricherà il PDF
    var a = document.createElement("a");
    a.setAttribute("id", "downloadFilePDF");
    a.download = filename;
    a.dataset.downloadurl = [contentType, a.download, a.href].join(':');
    a.href = window.URL.createObjectURL(file);

    // Necessario per Firefox
    document.body.appendChild(a);

    if (!isIEBrowser()) {
        // Browser che non sono Internet Explorer
        a.click();
    }
    else {
        // Internet Explorer
        window.navigator.msSaveBlob(file, filename);
    }
}