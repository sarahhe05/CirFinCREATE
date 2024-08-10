import json
from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/submit', methods=['POST'])
def submit():
    if request.method == 'POST':
        data = request.get_json()  # Get the JSON data sent from the frontend
        selected_ingredients = data['ingredients']

    # Process the selected ingredients as needed
    print(f"Received ingredients: {selected_ingredients}")

    # For this example, we'll just return a success message
    return jsonify({'message': 'Ingredients received successfully!'}), 200

        # Call your function with the dropdown values
    return render_template("index.html", display_choice = choice, display_result = result, display_safety = safety)

if __name__ == "__main__":
    app.run(debug=True)