import { Injectable } from '@angular/core';
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {UserService} from "../users/Shared/user.service";
import {BehaviorSubject} from "rxjs";
import {Router} from "@angular/router";

@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {
  private authenticationUrl = 'https://localhost:5001/api/authentication/authenticate';
  private loggedIn = new BehaviorSubject<boolean>(false);
  private token!: string;

  constructor(private httpClient: HttpClient, private userService: UserService, private router: Router) {

  }

  doLogin(formData: { password: string; username: string }) {
    const body = JSON.stringify(formData)
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    this.httpClient.request("POST", this.authenticationUrl, {
      body: body,
      responseType: 'text',
      observe: 'body',
      headers: headers
    }) .subscribe((response: string) => {
      console.log(response);
      this.token = response;
      this.userService.setLoggedIn(true, this.token);
      this.loggedIn.next(true);
      const userData = {
        token: this.token,
      };
      localStorage.setItem('user', this.token);
      this.router.navigateByUrl('/');
    });
  }

}
