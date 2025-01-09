  GNU nano 8.2                     dictionary.php                     Modified
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

