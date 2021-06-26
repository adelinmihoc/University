import { Injectable } from '@angular/core';
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {Router} from "@angular/router";

@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {
  private authenticationUrl = 'http://localhost/';

  constructor(private httpClient: HttpClient, private router: Router) {
  }

  doLogin(username: string) {
    localStorage.setItem('username', username);
    this.router.navigateByUrl('/');
  }

  doRegister() {

  }

  doLogout() {

  }

}
