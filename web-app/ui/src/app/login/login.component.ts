import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MatCardModule } from '@angular/material/card';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';
import { MatButtonModule } from '@angular/material/button';
import { MatSnackBar, MatSnackBarModule } from '@angular/material/snack-bar';
import { FormsModule } from '@angular/forms';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';

@Component({
    selector: 'app-login',
    standalone: true,
    imports: [
        CommonModule,
        MatCardModule,
        MatFormFieldModule,
        MatInputModule,
        MatButtonModule,
        MatSnackBarModule,
        FormsModule
    ],
    templateUrl: './login.component.html',
    styleUrls: ['./login.component.css']
})
export class LoginComponent {
    verificationCode: string = '';

    constructor(private http: HttpClient, private snackBar: MatSnackBar, private router: Router) { }

    login() {
        if (!this.verificationCode) {
            this.snackBar.open("Please enter a code", "Close", { duration: 3000 });
            return;
        }

        this.http.post('/api/login', { code: this.verificationCode }, { observe: 'response' })
            .subscribe({
                next: (response) => {
                    if (response.status === 200) {
                        this.snackBar.open("Login Successful", "Close", { duration: 3000 });
                        // Redirect or do something else
                    }
                },
                error: (error) => {
                    if (error.status === 401) {
                        this.snackBar.open("Invalid code", "Close", { duration: 3000 });
                    } else {
                        this.snackBar.open("An error occurred", "Close", { duration: 3000 });
                    }
                }
            });
    }
}
