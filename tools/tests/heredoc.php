<?php
echo 'Checking if you are using PH7 or PH8..';
/* Empty heredoc statement causes PH7 to skip the rest of the code */
echo <<<'EOT'
EOT;
/* If you see this comment, thin you are on PH7, ignore the rest of output */
var_dump($c);
echo 'Hello, you are running PH8!';

?>