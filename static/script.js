$(document).ready(function() {
    const availableIngredients = [
        "almond",
        "almond milk",
        "apple",
        "apple juice",
        "apricot",
        "artichoke",
        "asparagus",
        "avocado",
        "bacon",
        "banana",
        "beef",
        "beer",
        "beetroot",
        "black pepper",
        "blackberry",
        "bread",
        "broccoli",
        "butter",
        "carp",
        "carrot",
        "carrots",
        "cassava",
        "cauliflower",
        "celery",
        "cheddar",
        "cheese",
        "cherry",
        "chicken",
        "chocolate",
        "coconut",
        "coconut milk",
        "coffee",
        "cornflakes",
        "crackers",
        "cranberry juice",
        "cream",
        "cucumber",
        "dark chocolate",
        "duck",
        "egg",
        "eggplant",
        "fennel",
        "fish",
        "flaxseed",
        "garlic",
        "ginger",
        "goat cheese",
        "grape",
        "grapefruit",
        "ground coffee",
        "haddock",
        "honey",
        "jasmine rice",
        "ketchup",
        "lamb",
        "leek",
        "lemon",
        "lettuce",
        "lime",
        "lobster",
        "mackerel",
        "mango",
        "margarine",
        "mayonnaise",
        "melon",
        "milk",
        "milk chocolate",
        "mozzarella",
        "mushroom",
        "nuts",
        "oatmeal",
        "octopus",
        "olive oil",
        "onion",
        "orange",
        "orange juice",
        "pasta",
        "peach",
        "peanut",
        "peanut butter",
        "peanut oil",
        "pear",
        "pear juice",
        "peas",
        "pepper",
        "pesto",
        "pineapple",
        "pineapple juice",
        "plum",
        "pomegranate",
        "pork",
        "pork sausage",
        "potato",
        "pumpkin",
        "quinoa",
        "rabbit",
        "radish",
        "red wine",
        "rice",
        "rice milk",
        "ricotta",
        "salmon",
        "salt",
        "sesame seed",
        "shrimp",
        "soy milk",
        "soy yogurt",
        "soymilk",
        "spinach",
        "squid",
        "strawberry",
        "sugar",
        "sunflower oil",
        "sweet potato",
        "tofu",
        "tomato",
        "tomatoes",
        "trout",
        "tuna",
        "turkey",
        "vanilla",
        "veal",
        "vegetables",
        "watermelon",
        "white wine",
        "wine",
        "yeast",
        "yogurt",
        "zucchini"
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
                // DisplayRecipes(value);
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

    // // Handle form submission
    // $('#ingredientForm').submit(function(event) {
    //     event.preventDefault(); // Prevent the default form submission

    //     // Send the selected ingredients to the backend using AJAX
    //     $.ajax({
    //         url: '/submit', // Flask endpoint
    //         type: 'POST',
    //         contentType: 'application/json',
    //         data: JSON.stringify({ ingredients: selectedValues }),
    //         success: function(response) {
    //             console.log('Success:', response);
    //             // Optionally handle success, e.g., show a success message
    //         },
    //         error: function(error) {
    //             console.error('Error:', error);
    //             // Optionally handle error
    //         }
    //     });
    // });

    // function DisplayRecipes(value) {

    //     fetch('/search', {
    //         method: 'POST',
    //         headers: {
    //             'Content-Type': 'application/json'
    //         },
    //         body: JSON.stringify({ ingredient: value })
    //     })
    //     .then(response => response.json())
    //     .then(data => {
    //         document.getElementById('result').innerText = data.message;
    //     })
    //     .catch(error => console.error('Error:', error));
    // }

    // Submit form
    $('form').submit(function(event) {
        event.preventDefault();

        $.ajax({
            type: 'POST',
            url: '/submit',
            contentType: 'application/json',
            data: JSON.stringify({ selectedIngredients: selectedValues }),
            success: function(response) {
                displayResult(response.message);
            },
            error: function(xhr, status, error) {
                console.error('Error:', error);
            }
        });
    });

    // function displayResult(result) {
    //     // Assuming you want to display the result in the first accordion body
    //     $('#collapseOne .accordion-body').html(result);
    // }
    function displayResult(results) {
        // Clear existing accordion items
        $('#recipes-container').empty();
        
        // Loop through each result and create an accordion item
        results.forEach((item, index) => {
            const collapseId = `collapse${index+1}`;
            
            //Formats ingredients and directions as Lists
            const ingredientsList = item.ingredients.map(ingredient => `<li>${ingredient}</li>`).join('');
            const directionsList = item.directions.map(direction => `<li>${direction}</li>`).join('');
    
            const accordionItem = `
            </head>
                <link rel="stylesheet" href="/styles.css"/>  <!--Removed the static-->
                <div class="accordion-item">
                    <h2 class="accordion-header" id="heading${index + 1}">
                        <button class="accordion-button ${index === 0 ? '' : 'collapsed'}" 
                                type="button" data-bs-toggle="collapse" data-bs-target="#${collapseId}" 
                                aria-expanded="${index === 0}" aria-controls="${collapseId}">
                            <h2>${item.title}</h2>
                        </button>
                    </h2>
                    <div id="${collapseId}" class="accordion-collapse collapse ${index === 0 ? 'show' : ''}" data-bs-parent="#recipes-container">
                        <div class="accordion-body">
                            <h3>Ingredients</h3>
                            <ul>${ingredientsList}</ul>
                            <h3>Directions</h3>
                            <ul>${directionsList}</ul>
                            <h3>Carbon Footprint</h3>
                            <p>${item.carbonFootprint}</p>
                        </div>
                    </div>
                </div>
            `;
    
            $('#recipes-container').append(accordionItem);
        });
    }
});
