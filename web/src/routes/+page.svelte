<script>
	import { setupSerialConnection } from 'simple-web-serial';
	import { onMount } from 'svelte';
	import { writable } from 'svelte/store';
	import Modal from '../lib/Modal.svelte';

	// let sensors = writable({
	// 	temp: '',
	// 	humi: '',
	// 	pres: ''
	// });

	let arduinoIsConnected = false;

	function setupConnection() {
		const connection = setupSerialConnection();
		console.log(connection);
		connection.startConnection();
		arduinoIsConnected = true;
		console.log(connection);

		connection.on('touch', (data) => {
			touch = data;

			console.log(data);
		});

		connection.on('sensors', (data) => {
			sensors = data;
		});
	}

	// onMount(() => {
	// 	navigator.geolocation.getCurrentPosition((position) => {
	// 		console.log(position);
	// 	});
	// });

	let touch;
	let sensors = {
		temp: '20.00',
		humi: '50',
		pres: '98.28'
	};
</script>

<div class="page-wrapper">
	<div class="header">
		<div>
			<span>Current location</span>
			<h1>Stuttgart</h1>
		</div>
		<div class="connection-status">
			{#if arduinoIsConnected}
				<span class="sensor-indicator"></span><span>Sensor connected</span>
			{:else}
				<span class="sensor-indicator offline"></span>
				<button type="button" on:click={setupConnection}>Connect sensor</button>
			{/if}
		</div>
	</div>

	<div class="data-categories">
		<a class="data-item" href="/temperature">
			<h2>{sensors.temp} °C</h2>
			<p>Temperature</p>
		</a>
		<a class="data-item" href="/humidity">
			<h2>{sensors.humi} %</h2>
			<p>Humidity</p>
		</a>
		<a class="data-item" href="/pressure">
			<h2>{sensors.pres} kPa</h2>
			<p>Pressure</p>
		</a>
	</div>
</div>

<style>
	.page-wrapper {
		display: flex;
		align-content: space-between;
		height: 100%;
		flex-direction: column;
	}

	.header {
		display: flex;
		justify-content: space-between;
		margin-bottom: auto;
		align-items: center;
	}

	.data-categories {
		display: flex;
		flex-direction: row;
		gap: 1rem;
	}

	.data-item {
		border: 2px solid black;
		padding: 1rem;
		flex: 1 1 0px;
		border-radius: 1rem;
		text-decoration: none;
		color: unset;
	}

	.data-item:hover {
		background-color: black;
		color: white;
		cursor: pointer;
	}

	.data-item h2 {
		margin-bottom: 1rem;
	}

	.connection-status {
		border-radius: 999px;
		border: 2px solid black;
		display: flex;
		gap: 0.5rem;
		padding: 1rem;
		align-items: center;
	}

	.connection-status:hover {
		background-color: black;
		color: white;
		cursor: pointer;
	}

	.sensor-indicator {
		border-radius: 100%;
		width: 0.75rem;
		height: 0.75rem;
		background-color: greenyellow;
	}

	.sensor-indicator.offline {
		background-color: indianred;
	}

	button {
		appearance: none;
		border: none;
		background: none;
		font-size: 1rem;
	}
</style>
