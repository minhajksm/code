package main

import (
	"log"
	"net/http"

	"github.com/emicklei/go-restful"
)

type User struct {
	Id   string
	Name string
}

type UserList struct {
	Users []User
}

//
// This example shows how to use the CompressingResponseWriter by a Filter such
// that encoding can be enabled per WebService or per Route (instead of per container).
// Using restful.DefaultContainer.EnableContentEncoding(true) will encode all responses
// served by WebServices in the DefaultContainer.
//
// Set Accept-Encoding to gzip or deflate and look at the response headers
//   GET http://localhost:8080/users/42
//

func main() {
	restful.Add(NewUserService())
	log.Printf("start listening on localhost:8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

func NewUserService() *restful.WebService {
	ws := new(restful.WebService)
	ws.
		Path("/users").
		Consumes(restful.MIME_XML, restful.MIME_JSON).
		Produces(restful.MIME_JSON, restful.MIME_XML)

	// install a response encoding filter
	ws.Route(ws.GET("/{user-id}").Filter(encodingFilter).To(findUser))
	return ws
}

// Route Filter (defines FilterFunction)
func encodingFilter(req *restful.Request, resp *restful.Response, chain *restful.FilterChain) {
	log.Printf("[encoding-filter] %s,%s\n", req.Request.Method, req.Request.URL)
	// wrap responseWriter into a compressing one
	compress, _ := restful.NewCompressingResponseWriter(resp.ResponseWriter, restful.ENCODING_GZIP)
	resp.ResponseWriter = compress // override original ResponseWriter
	defer func() {
		compress.Close()
	}()
	chain.ProcessFilter(req, resp)
}

//
// GET http://localhost:8080/users/42
//
func findUser(request *restful.Request, response *restful.Response) {
	log.Printf("findUser")
	response.WriteEntity(User{"42", "Gandalf"})
}
