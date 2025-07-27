setInterval(myFunction, 1000);

function myFunction() {
    document.addEventListener("DOMContentLoaded", () => 
        document.querySelectorAll("a[href^='https://www.scs.ubbcluj.ro']").forEach(link => link.remove())
    );
}