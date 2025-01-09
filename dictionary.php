<?php
$servername = "localhost";
$username = "deemajabi";  
$password = "dodo1122002";      
$dbname = "dictionary";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

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
    <title>Dictionary Application</title>
</head>
<body>
    <h1>Simple Dictionary</h1>
    <form method="POST" action="">
        <label for="word">Enter a word:</label>
        <input type="text" id="word" name="word" required>
        <button type="submit">Search</button>
    </form>

    <?php if (isset($definition)): ?>
        <h2>Definition:</h2>
        <p><?php echo htmlspecialchars($definition); ?></p>
    <?php endif; ?>
</body>
</html>
