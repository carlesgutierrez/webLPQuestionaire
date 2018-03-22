// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================

var JSONRPCClient; ///< The core JSONRPC WebSocket client.

function addError(error) {
    console.log(error);
}

function onWebSocketOpen(ws) {
    console.log("on open");
    console.log(ws);
}

function onWebSocketMessage(evt) {
    console.log("on message:");
    console.log(evt.data);
}

function onWebSocketClose() {
    console.log("on close");
}

function onWebSocketError() {
    console.log("on error");
}

function initializeButtons() {

    //Get all questions
    $('#get-questions').on('click', function() {
        var $this = $(this);
        JSONRPCClient.call('get-questions-server',
            null,
            function(result) {
                $('#questions-to-receive').empty();
                for(var i = 0; i< result.length; i++){
                    question = result[i];
                    console.log(question);

                    $('#questions-to-receive').append("<li>"+question.id+" "+question.question+"</li>"); 
                }

                console.log(result);
            },
            function(error) {
                addError(error);
            });
    });


    //Set a new question
    $('#set-question').on('click', function() {
        var $this = $(this);
        console.log($('#idquestion-to-send').val());
        console.log($('#question-to-send').val());

        var auxQuestion = new Array($('#idquestion-to-send').val(), $('#question-to-send').val());

        JSONRPCClient.call('set-question-server',
            auxQuestion,
            function(result) {},
            function(error) {
                addError(error);
            });

        JSONRPCClient.call('get-questions-server',
            null,
            function(result) {
                $('#questions-to-receive').empty();
                for(var i = 0; i< result.length; i++){
                    question = result[i];
                    console.log(question);

                    $('#questions-to-receive').append("<li>"+question.id+" "+question.question+"</li>"); 
                }

                //console.log(result);
            },
            function(error) {
                addError(error);
            });
    });

    //Get a questions and update it
    $('#update-question').on('click', function() {
        var $this = $(this);
        console.log("update");
        console.log($('#idquestion-to-update').val());
        console.log($('#question-to-update').val());

        var auxQuestion = new Array($('#idquestion-to-update').val(), $('#question-to-update').val());

        JSONRPCClient.call('update-questionId-server',
            auxQuestion,
            function(result) {},
            function(error) {
                addError(error);
            });

        JSONRPCClient.call('get-questions-server',
            null,
            function(result) {
                $('#questions-to-receive').empty();
                for(var i = 0; i< result.length; i++){
                    question = result[i];
                    console.log(question);

                    $('#questions-to-receive').append("<li>"+question.id+" "+question.question+"</li>"); 
                }

                console.log(result);
            },
            function(error) {
                addError(error);
            });
    });


    //Delete a question
    $('#delete-question').on('click', function() {
        var $this = $(this);
        var auxQuestion2Delete = $('#idquestion-to-delete').val();

        JSONRPCClient.call('delete-question-server',
            auxQuestion2Delete,
            function(result) {
            },
            function(error) {
                addError(error);
            });

       JSONRPCClient.call('get-questions-server',
            null,
            function(result) {
                $('#questions-to-receive').empty();
                for(var i = 0; i< result.length; i++){
                    question = result[i];
                    console.log(question);

                    $('#questions-to-receive').append("<li>"+question.id+" "+question.question+"</li>"); 
                }

                console.log(result);
            },
            function(error) {
                addError(error);
            });

            });
    /*$('#ping').on('click', function() {
        console.log("pinging");
        var $this = $(this);
        JSONRPCClient.notify('ping');
    });


    $('#pong').on('click', function() {
        console.log("poinging");
        var $this = $(this);
        JSONRPCClient.notify('pong');
    });*/

                //$('#question-to-update').val(result);
            //var myJsonResult = result;
            //console.log(myJsonResult);
            //var myFisrtQuestion = myJsonResult[0].question;
           // console.log(myFisrtQuestion);
            ///var myFisrtQuestion = myJsonResult[0]question;
            ///var myFisrtQuestion = myJsonResult[0]["question"];
            //$('#text-to-recieve').val(myFisrtQuestion); //Just returning one for debuggin
}

$(document).ready(function() {
    // Initialize our JSONRPCClient
    JSONRPCClient = new $.JsonRpcClient({
        ajaxUrl: getDefaultPostURL(),
        socketUrl: getDefaultWebSocketURL(), // get a websocket for the localhost
        onmessage: onWebSocketMessage,
        onopen: onWebSocketOpen,
        onclose: onWebSocketClose,
        onerror: onWebSocketError
    });

    initializeButtons();

});