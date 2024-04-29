/**
 *
 * @param node The element provided by svelte
 * @param targetElementOrSelector The portal anchor, document.querySelector('#popup-container')
 * @returns Function when the parent is destroyed
 */
export function portal(node, targetElementOrSelector) {
	const targetElement =
		typeof targetElementOrSelector == 'string'
			? document.querySelector(targetElementOrSelector)
			: targetElementOrSelector;

	if (targetElement == null) throw new Error('Target element not found/undefined.');

	targetElement.append(node);

	return {
		destroy() {
			node.remove();
		}
	};
}
