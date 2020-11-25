<?php

final class Exec {

    /**
     * Program path
     * @var string
     */
    private $path;

    /**
     * Command-line arguments
     * @var string
     */
    private $args = array();

    /**
     * Redirect STDIN pipe
     * @example /dev/null
     * @example 2
     * @var string
     */

    private $stderr = null;
    /**
     * Redirect STDOUT pipe
     * @example /dev/null
     * @example 2
     * @var string
     */
    private $stdout = null;

    /**
     * Run a program in a shell.
     * @param string $path Path of the program to run.
     */
    public function __construct($path) {
        $this->path = $path;
    }

    /**
     * Build Exec class
     * @return Exec
     */
    public static function factory($path) {
        return new self($path);
    }

    /**
     * Set new command-line argument.
     * @param string $argument
     * @return Exec
     */
    public function setArgument($argument) {
        $this->args[] = (string)$argument;
        return $this;
    }

    /**
     * Redirect STDERR pipe
     * @example /dev/null
     * @param string $redirect
     * @return Exec
     */
    public function setStderr($redirect) {
        $this->stderr = $redirect;
        return $this;
    }

    /**
     * Redirect STDOUT pipe
     * @example /dev/null
     * @param string $redirect
     * @return Exec
     */
    public function setStdout($redirect) {
        $this->stdout = $redirect;
        return $this;
    }

    protected static function escapeShellCommand($command, &$append = null) {
        if ($append != null)
            $append = sprintf("%s %s", $append, self::escapeShellCommand($command));
        return sprintf("\"%s\"", escapeshellcmd($command));
    }

    /**
     * Run a program and takes the output.
     * @return string
     */
    public function call() {

        /* Set Path */
        $cmd = self::escapeShellCommand($this->path);

        /* Set command-line arguments*/
        foreach ($this->args as $arg) {
            self::escapeShellCommand($arg, $cmd);
        }

        /* Redirect STDERR */
        if ($this->stderr !== null) 
            $cmd .= " 2> ". escapeshellcmd($this->stderr);

        /* Redirect STDOUT */
        if ($this->stdout !== null)
            $cmd .= " 1> ". escapeshellcmd($this->stdout);

        /* Close STDIN */
        $cmd .= " <&-";

        /* Execute */
        return shell_exec($cmd);
    }


}

