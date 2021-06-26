import { Injectable } from '@angular/core';
import {HttpClient, HttpHeaders, HttpParams} from "@angular/common/http";
import {map} from "rxjs/operators";
import {Observable} from "rxjs";
import {User} from "./user.model";

@Injectable({
  providedIn: 'root'
})
export class UserService {
  private usersUrl = 'https://localhost:5001/api/Users';
  private usersFilterUrl = 'https://localhost:5001/api/Filter';
  private loggedIn = false;
  private token!: string | undefined;

  setLoggedIn(loggedIn: boolean, token?: string) {
    this.loggedIn = loggedIn;
    this.token = token;
  }

  constructor(private httpClient: HttpClient) { }

  getUsers(): Observable<User[]> {
    let token = localStorage.getItem("user");
    if (token == null) {
      token = "";
    }
    let headers = new HttpHeaders();
    headers = headers.append('Authorization', `Bearer ${token}`);
    const users: Observable<User[]> = this.httpClient
      .get<Array<User>>(this.usersUrl, {headers: headers});
    console.log(users);
    return users;
  }

  filterUsers(role: string): Observable<User[]> {
    const url = `${this.usersFilterUrl}/${role}`;
    let token = localStorage.getItem("user");
    if (token == null) {
      token = "";
    }
    let headers = new HttpHeaders();
    headers = headers.append('Authorization', `Bearer ${token}`);
    const users: Observable<User[]> = this.httpClient
      .get<Array<User>>(url, {headers: headers});
    console.log(users);
    return users;
  }

  saveUser(user: User) {
    console.log(user);
    let token = localStorage.getItem("user");
    if (token == null) {
      token = "";
    }
    let headers = new HttpHeaders();
    headers = headers.append('Authorization', `Bearer ${token}`);
    return this.httpClient
      .post<User>(this.usersUrl, user, {observe: 'response', headers: headers});
  }

  deleteUser(userId: number) {
    const url = `${this.usersUrl}/${userId}`;
    let token = localStorage.getItem("user");
    if (token == null) {
      token = "";
    }
    let headers = new HttpHeaders();
    headers = headers.append('Authorization', `Bearer ${token}`);
    return this.httpClient.delete(url, {headers: headers}).subscribe(response => console.log(response));
  }

  updateUser(user: User) {
    console.log("user is", user);
    const url = `${this.usersUrl}/${user.id}`;
    console.log(user.id);
    let token = localStorage.getItem("user");
    if (token == null) {
      token = "";
    }
    let headers = new HttpHeaders();
    headers = headers.append('Authorization', `Bearer ${token}`);
    return this.httpClient
      .put<User>(url, user, {headers: headers}).subscribe(v => console.log(v));
  }
}
