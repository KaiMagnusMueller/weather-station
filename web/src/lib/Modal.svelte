<script>
	import { portal } from '$lib/actions';
	export let title = 'Lorem ipsum';

	function attachModal(node) {}
</script>

<div use:portal={document.querySelector('#modal-anchor')}>
	<h2>{title}</h2>

	<slot></slot>
</div>
