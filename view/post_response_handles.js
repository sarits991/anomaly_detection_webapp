function OnLoad() {
    let template = {'<>': 'ul','html':'<li><p style="font-size:20px;">feature1: ${feature1} <br>feature2: ${feature2} <br> timesteps: ${range}</p> </li>'};
    let templateError = {'<>': 'div','html':'<p style="color: red;font-size:25px;"> ${error}</p>'};
    let iframe = document.getElementById("result");
    let data = iframe.contentDocument.body.innerText;
    if(data == null || typeof data == "undefined" || data == "")
        return;
    let json = JSON.parse(data);
    if(json.hasOwnProperty('error')){
        iframe.contentDocument.write(json2html.render(data,templateError));
    }
    else{
        iframe.contentDocument.write(json2html.render(data,template));
    }
}

function pending() {
    let iframe = document.getElementById("result");
    let body = iframe.contentWindow.document.querySelector('body');
    let text  = iframe.contentDocument.body;
    if(text != null)
        text.innerHTML = "";
    iframe.contentDocument.write("<p style='font-size: 25px;'>pending..</p>");
}