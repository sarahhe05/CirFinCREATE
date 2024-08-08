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
});
