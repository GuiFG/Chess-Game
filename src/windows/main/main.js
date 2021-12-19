import { Board } from '../modules/board/board.js'

$(document).ready(function() {
    const board = Board()
    board.create()
    board.draw()
})



