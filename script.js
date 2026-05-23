async function getSuggestions() {
    const inputElement = document.getElementById("username");  // ✅ the element
    const username = inputElement.value.trim();                // ✅ the value
    const suggestionsDiv = document.getElementById("suggestions");

    if (!username) {
        suggestionsDiv.textContent = "Please enter a name";
        return;
    }

    try {
        const response = await fetch("http://localhost:3000/suggest", {
            method: "POST",
            headers: { "Content-Type": "text/plain" },
            body: username                                // ✅ send only the string
        });

        if (!response.ok) throw new Error(`HTTP error ${response.status}`);

        // const data = await response.json();
        const data = await response.json();
suggestionsDiv.innerHTML = ""; // clear old suggestions

if (data.length > 0) {
    data.forEach(name => {
        const card = document.createElement("div");
        card.className = "card";
        const image = getImageForUser(name);

        // Optional: add profile icon
        card.innerHTML = `
            <img src= ${image} alt="Avatar">
            <p><strong>${name}</strong></p>
            <button class="follow-btn">Follow</button>
        `;

        suggestionsDiv.appendChild(card);
    });
   document.querySelectorAll(".follow-btn").forEach(button => {
    button.addEventListener("click", (e) => {
        const btn = e.target;
        const username = btn.parentElement.querySelector("strong").textContent;

        // Update button text
        btn.textContent = "Followed";

        // Optional: disable button to prevent repeated clicks
        btn.disabled = true;
        btn.style.backgroundColor = "green"; // Optional: grey out the button

        // You can also send a follow request here if needed
        console.log(`Followed ${username}`);
    });
});

} else {
    suggestionsDiv.textContent = "No suggestions found";
}

    } catch (error) {
        console.error("Fetch failed:", error);
        suggestionsDiv.textContent = "Error: Could not fetch suggestions";
    }

}

function getImageForUser (name) {
    if(name === "sowmya")
    {
        return "1705921786095.jpg";
    }
    else if (name === "srinidhi")
    {
        return "1705921786004.jpg";
    }
    else if (name === "riya"){
        return "1705921787778.jpg";
    }
    else if(name === "sasikumar"){
        return "123.jpeg"
    }
    else {
        return "055-12.jpg"
    }
}
