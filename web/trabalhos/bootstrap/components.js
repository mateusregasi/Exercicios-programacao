class NavBar extends HTMLElement{
    connectedCallback(){
        this.innerHTML = `
<nav class="navbar navbar-expand-sm" id="nav">
    <div class="container">
        <button class="navbar-toggler color-white" type="button" data-bs-toggle="collapse" data-bs-target="#nav" aria-controls="nav" aria-expanded="false"><span class="navbar-toggler-icon"></span></button>
        <a href="#" class="navbar-brand">MR</a>
        <div class="collapse navbar-collapse" id="nav">
            <ul class="navbar-nav ms-auto d-flex gap-3">
                <li class="nav-item active"><a href="#" class="nav-link">SOBRE</a></li>
                <li class="nav-item active"><a href="#" class="nav-link">PROJETOS</a></li>
                <li class="nav-item active"><a href="#" class="nav-link">CONTATOS</a></li>
                <li class="nav-item active"><a href="#" class="nav-link">BLOG</a></li>
                <li><a href=""><img src="_img/email.svg" alt="" class="navbar-icon color-white m-1 ms-5"></a></li>
                <li><a href=""><img src="_img/instagram.svg" alt="" class="navbar-icon color-white m-1"></a></li>
                <li><a href=""><img src="_img/twitter.svg" alt="" class="navbar-icon color-white m-1"></a></li>
            </ul>
        </div>
    </div>
</nav>`
    }
}

class InitialDisplay extends HTMLElement{
    connectedCallback(){
        this.innerHTML = `
<div class="container-fluid initial_display">

    <figure><img src="_img/mateus1.png"></figure>

    <aside class="left-100">
        
        <h1 class="text-center">Mateus Regasi</h1>

        <p class="text-center">Desenvolvedor, eterno estudante e apaixonado por tecnologia.</p>

        <button type="button" class="btn btn-primary">Mais sobre mim</button>

    </aside>

    <footer class="position-sticky top-100"></footer>

</div>`
    }
}

class Languages extends HTMLElement{
    connectedCallback(){
        this.innerHTML = `
<div class="languages container-fluid">
    <div class="rounded-circle" style="top: -25px;"></div>
    <div class="square">
        <h1>Linguagens:</h1>
        <hr>
        <div class="row">
            <div class="col-sm">
                <img src="_img/python.svg" alt="" class="color-white">
                <img src="_img/sql.svg" alt="" class="color-white">
            </div>
            <div class="col-sm">
                <img src="_img/php.svg" alt="" class="color-white">
                <img src="_img/prolog.svg" alt="" class="color-white">
            </div>
            <div class="col-sm">
                <img src="_img/c.svg" alt="" class="color-white">
                <img src="_img/java.svg" alt="" class="color-white">
            </div>
        </div>
    </div>
    <div class="rounded-circle" style="bottom: -25px;">
        <img src="_img/triangle.svg" alt="" class="color-white">
    </div>
</div>`
    }
}

class ProjectCarousel extends HTMLElement{
    connectedCallback(){
        this.innerHTML = `
<div id="projeto-carousel" class="carousel slide" data-ride="carousel">
    <ol class="carousel-indicators">
        <li data-target="#projeto-carousel" data-slide-to="0" class="active"></li>
        <li data-target="#projeto-carousel" data-slide-to="1"></li>
        <li data-target="#projeto-carousel" data-slide-to="2"></li>
    </ol>
    <div class="carousel-inner">
        <div class="carousel-item active">
        <img class="d-block w-100" src="_img/generator.png" alt="First slide">
        </div>
        <div class="carousel-item">
        <img class="d-block w-100" src="_img/smoothed_perlin_noise.png" alt="Second slide">
        </div>
        <div class="carousel-item">
        <img class="d-block w-100" src="_img/random_states_on_grid.png" alt="Third slide">
        </div>
    </div>
    <a class="carousel-control-prev" href="#projeto-carousel" role="button" data-slide="prev">
        <span class="carousel-control-prev-icon" aria-hidden="true"></span>
        <span class="sr-only"></span>
    </a>
    <a class="carousel-control-next" href="#projeto-carousel" role="button" data-slide="next">
        <span class="carousel-control-next-icon" aria-hidden="true"></span>
        <span class="sr-only"></span>
    </a>
</div>`
    }
}

class CustomFooter extends HTMLElement{
    connectedCallback(){
        this.innerHTML = `

`
    }
}

// class NavBar extends HTMLElement{
//     connectedCallback(){
//         this.innerHTML = 
//     }
// }




customElements.define('custom-navbar', NavBar)
customElements.define('initial-display', InitialDisplay)
customElements.define('languages-display', Languages)
customElements.define('project-carousel', ProjectCarousel)
customElements.define('custom-footer', CustomFooter)
