// The static type (or just type) of a variable is the type defined by its
// declaration. Variables of interface type also have a distinct dynamic
// type, which is the actual type of the value stored in the variable at
// run time. The dynamic type may vary during execution but is always assignable
// to the static type of the interface variable. For non-interface types,
// the dynamic type is always the static type.
//
// The interface{} type is the interface that has no methods. Since there
// is no implements keyword, all types implement at least zero methods, and
// satisfying an interface is done automatically, all types satisfy the empty
// interface. That means that if you write a function that takes an interface{}
// value as a parameter, you can supply that function with any value.
//
// An interface value is constructed of two words of data; one word is used
// to point to a method table for the value’s underlying type, and the other
// word is used to point to the actual data being held by that value.

package main

import "fmt"

func main() {
	// 'a' can be any value, an int or string.
	var a interface{} = 2 // a has dynamic type int and value 2 (static type interface{})
	fmt.Println(a)

	a = "Change to string type" // a changes its dynamic type to string (static type interface{})
	fmt.Println(a)

	// We convert 'a interface{}' type using a dot and the required
	// type in parentheses.  This is called type assertion.
	b := a.(string) // b has static type string
	fmt.Println(b)

	// If we can't convert a variable by a given type, go will panic.
	// Or we can accept a second return value to check the status.
	v, ok := a.(float32)
	if ok {
		fmt.Println(v)
	} else {
		fmt.Println("Cannot convert a to float32")
	}

	// Take action based on type (type switch).
	switch t := a.(type) {
	case string:
		fmt.Println("a has type string", t)
	case int32, int64:
		fmt.Println("a has type int", t)
	case float32, float64:
		fmt.Println("a has type float", t)
	default:
		fmt.Println("unknown")
	}

	var f float32 = 1.1
	i := int32(f) // type conversion
	fmt.Println(i)
}
