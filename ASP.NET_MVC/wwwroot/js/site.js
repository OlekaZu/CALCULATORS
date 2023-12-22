// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

function addToInputStr(ch) {
    var equalBtnValue = document.getElementById('calculateButton').value;
    if (equalBtnValue == 'clickYes') {
        document.getElementById('calculateButton').value = 'clickNo';
        cleanInputStr();
    }
    let element = document.getElementById('inputStrArea');
    element.textContent += ch;
}

function cleanInputStr() {
    let element_input = document.getElementById('inputStrArea');
    element_input.textContent = '';
  document.getElementById('resultStrInput').value = '0';
}

function deleteLastElementInInputStr() {
    let element = document.getElementById('inputStrArea');
    element.textContent = element.textContent.trim().slice(0, -1);
}

function addSelectedToInputStr() {
    var sel = document.getElementById('selectHistory');
    var val = sel.options[sel.selectedIndex].text;
    document.getElementById('inputStrArea').textContent = val;
    document.getElementById('resultStrInput').value = '';
}

function doActiveInput(nameCheckBox, nameInput) {
    if (nameCheckBox.checked == true) {
        nameInput.disabled = false;
    } else if (nameCheckBox.checked == false) {
        nameInput.disabled = true;
        nameInput.value = '0';
    }
}

function goToGraphPage() {
    var formula = document.getElementById('inputStrArea').value;
    localStorage.setItem('transferFormula', formula);
    window.location.href = '/Home/Graph';
}