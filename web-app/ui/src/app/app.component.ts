import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
    selector: 'app-root',
    standalone: true,
    imports: [CommonModule],
    template: `<h1>Welcome to Warehouse Under Control</h1>`,
    styles: [],
})
export class AppComponent {
    title = 'ui';
}
