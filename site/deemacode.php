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
