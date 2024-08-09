$(document).ready(function() {
    const availableIngredients = [
        "Tomato",
        "Onion",
        "Garlic",
        "Basil"
        // Add more ingredients here
    ];

    const selectedValues = [];

    $("#ingredientSearch").autocomplete({
        source: availableIngredients,
        minLength: 1,
        autoFocus: true,
        select: function(event, ui) {
            const value = ui.item.value;
            if (!selectedValues.includes(value)) {
                selectedValues.push(value);
                displaySelectedIngredients();
            }
            $(this).val(''); // Clear the input field after selection
            return false; // Prevent the selected value from being put into the input field
        }
    });

    function displaySelectedIngredients() {
        const container = $('#selectedIngredients');
        container.empty();
        selectedValues.forEach(function(value) {
            const tag = $(`<div class="tag">${value} <span>&times;</span></div>`);
            tag.find('span').click(function() {
                removeIngredient(value);
            });
            container.append(tag);
        });
    }

    function removeIngredient(value) {
        const index = selectedValues.indexOf(value);
        if (index !== -1) {
            selectedValues.splice(index, 1);
            displaySelectedIngredients();
        }
    }

    // Handle form submission
    $('#ingredientForm').submit(function(event) {
        event.preventDefault(); // Prevent the default form submission

        // Send the selected ingredients to the backend using AJAX
        $.ajax({
            url: '/submit', // Flask endpoint
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({ ingredients: selectedValues }),
            success: function(response) {
                console.log('Success:', response);
                // Optionally handle success, e.g., show a success message
            },
            error: function(error) {
                console.error('Error:', error);
                // Optionally handle error
            }
        });
    });
});
