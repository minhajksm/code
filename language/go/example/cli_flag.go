package main

// Go provides a `flag` package supporting basic command-line flag parsing.
// Note that the flag package requires all flags to appear before positional
// arguments (otherwise the flags will be interpreted as positional arguments).
import (
	"flag"
	"fmt"
)

func main() {
	// Basic flag declarations are available for string, integer, and boolean
	// options. Here we declare a string flag `word` with a default value "foo"
	// and a short description. This `flag.String` function returns a string
	// pointer (not a string value); we'll see how to use this pointer below.
	wordPtr := flag.String("word", "foo", "a string")

	// This declares `numb` and `fork` flags, using a similar approach to the
	// `word` flag.
	numbPtr := flag.Int("numb", 42, "an int")
	boolPtr := flag.Bool("fork", false, "a bool")

	// It's also possible to declare an option that uses an existing var
	// declared elsewhere in the program. Note that we need to pass in a
	// pointer to the flag declaration function.
	var svar string
	flag.StringVar(&svar, "svar", "bar", "a string var")

	// Once all flags are declared, call `flag.Parse()` to execute the
	// command-line parsing.
	flag.Parse()

	// Here we'll just dump out the parsed options and any trailing positional
	// arguments. Note that we need to dereference the points with e.g. `*wordPtr`
	// to get the actual option values.
	fmt.Println("word:", *wordPtr)
	fmt.Println("numb:", *numbPtr)
	fmt.Println("fork:", *boolPtr)
	fmt.Println("svar:", svar)
	fmt.Println("tail:", flag.Args())
}
