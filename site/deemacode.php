<?php
// Database connection details
$servername = "db";
$username = "root";  
$password = "dodo1122002";     
$dbname = "dictionary";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$definition = ""; // Initialize the definition variable

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $search_word = $conn->real_escape_string($_POST['word']);
    $sql = "SELECT definition FROM words WHERE word = '$search_word'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        $definition = $row['definition'];
    } else {
        $definition = "Word not found.";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Word Lookup</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            background-color: #f9f9f9;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }
        .container {
            background-color: #fff;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            text-align: center;
            max-width: 400px;
            width: 100%;
        }
        h1 {
            color: #333;
            font-size: 24px;
            margin-bottom: 20px;
        }
        input[type="text"] {
            width: calc(100% - 22px);
            padding: 10px;
            margin-bottom: 10px;
            border: 1px solid #ccc;
            border-radius: 5px;
            font-size: 16px;
        }
        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
        }
        button:hover {
            background-color: #45a049;
        }
        .result {
            margin-top: 20px;
            padding: 10px;
            background-color: #e9f7ef;
            border: 1px solid #4CAF50;
            border-radius: 5px;
            color: #333;
            font-size: 16px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Word Lookup</h1>
        <form method="POST" action="">
            <input type="text" name="word" placeholder="Enter a word" required>
            <button type="submit">Lookup</button>
        </form>
        <?php if ($_SERVER["REQUEST_METHOD"] == "POST"): ?>
            <div class="result">
                <strong>Definition:</strong> <?php echo htmlspecialchars($definition); ?>
            </div>
        <?php endif; ?>
    </div>
</body>
</html>
