<div class="app-wrapper">
	<div id="modal-anchor"></div>
	<slot></slot>
</div>

<style>
	:global(body) {
		margin: 0;
		height: 100vh;

		font-family: sans-serif;
	}

	:global(*) {
		box-sizing: border-box;
	}

	:global(h1, h2, h3, h4, p) {
		margin: 0;
	}

	.app-wrapper {
		padding: 1rem;
		height: 100%;
	}

	#modal-anchor {
		position: absolute;
	}
</style>
