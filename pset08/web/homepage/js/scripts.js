function validateForm(e) {
    if(e.preventDefault) e.preventDefault();
    
    const name = form.yourname.value;
    const email = form.youremail.value;
    const subject = form.yoursubject.value;
    const text = form.yourmessage.value;

    if(name === '' || email === '')
    {
        alert ("Name and email are mandatory");
        return false;
    }
    
    alert('Your message will be sent now. Thank you');
    form.submit();
}

const form = document.querySelector('#formsubmit');
if(form.attachEvent) {
    form.attachEvent("submit", validateForm);
} else {
    form.addEventListener("submit", validateForm);
}