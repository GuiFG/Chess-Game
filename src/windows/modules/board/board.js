function Board() {
    const options = {
        'id': 'board',
        'width' : 600,
        'height' : 600,
        'squares' : 64,
        'square-color' : ['white', 'black'],
        'border-color' : 'black'
    }
    

    function create() {
        const div = document.createElement('div')

        div.id = options['id']
        div.style.width = getStringPixel(options['width'])
        div.style.height = getStringPixel(options['height'])
        div.style.border = "thick solid " + options['border-color']
        
        console.log(div)

        const body = document.getElementById('main')
        body.appendChild(div)
    }
    
    function draw() {
        const div = document.getElementById(options['id'])
    
        if (!div)
        {
            console.log(`Error to get the board. Not found id: ${options['id']}`)
            return false
        }
        
        const square = getSquareSize(options['width'], options['height'], options['squares'])
        
        drawSquares(square, options['squares'])
   
        return true
    }
    
    function getSquareSize(width, height, squares) {
        squares = Math.sqrt(squares)
        
        width /= squares 
        height /= squares 
    
        return {
            'width' : width,
            'height' : height
        }
    }

    function drawSquares(square, total) {
        const ranks = Math.sqrt(total)
        const files = ranks
        const board = document.getElementById(options['id'])

        for (let i = 0; i < ranks; i++)
        {
            let rank = document.createElement('div')

            rank = setConfigRank(rank, square['width'] * ranks, square['height'])

            for (let k = 0; k < files; k++)
            {
                let sq = document.createElement('div')
                
                sq = setConfigSquare(sq, i, k, square)

                rank.appendChild(sq)
            }

            board.appendChild(rank)
        }
    }

    function setConfigRank(rank, width, height) {
        rank.style.width = getStringPixel(width)
        rank.style.height = getStringPixel(height)

        return rank
    }

    function setConfigSquare(sq, i, k, square)
    {
        sq.className = `${String.fromCharCode(97 + k)}${i+1}` 
        sq.style.display = 'inline-block'

        sq.style.top = getStringPixel(square['height'])
        sq.style.left = getStringPixel(square['width'] * k)

        
        sq.style.width = getStringPixel(square['width'])
        sq.style.height = getStringPixel(square['height'])

        const idxColor = (i % 2) ^ (k % 2)
        sq.style.background = options['square-color'][idxColor]

        return sq
    }

    function getStringPixel(value) {
        return `${value}px`
    }
    

    return {
        create,
        draw
    }
}


export { Board }